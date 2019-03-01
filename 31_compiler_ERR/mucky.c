/*https://www.quora.com/How-do-I-make-a-compiler-for-C-from-scratch-Are-there-any-tutorial-or-source-from-which-I-can-learn*/
/*[Henry Dietz; University of Kentucky]*/
/*	mucky.c

	MIPS uCompiler from KentuckY.
*/

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

int	haveinput = 0;

char	*prelab = "L";
int	callerreg, calleereg;
int	scope = 0;
int	labnum = 0;	/* next compiler-generated label */
int	lexsym;

int	beginlab, endlab;	/* for function begin/end code */
int	gpoffset, fpoffset;	/* for globals/locals */
int	isleaf;			/* is this a leaf procedure? */
int	linestart = 0;		/* start of current line */

#define	DATABASE	0x10000000

#define	INT	'a'
#define	IF	'b'
#define	ELSE	'c'
#define	WHILE	'd'
#define	RETURN	'e'
#define	FUNC	'f'
#define	WORD	'g'
#define	NUM	'h'
#define	DO	'i'
#define	VAR	'j'
#define	AFP	'k'
#define	ASP	'l'
#define	AGP	'm'
#define	SHORT	'n'
#define	CHAR	'o'
#define RETVAL	'p'
#define	MULBY4	'q'
#define	MULBY2	'r'
#define	STRING	's'
#define	FOR	't'
#define	GOTO	'u'
#define	TARGET	'v'

#define	EQ	'A'
#define	NE	'B'
#define	GE	'C'
#define	LE	'D'
#define	SL	'E'
#define	PP	'F'
#define	MM	'G'
#define	OE	'H'
#define	XE	'I'
#define	AE	'J'
#define	PE	'K'
#define	ME	'L'
#define	TE	'M'
#define	DE	'N'
#define	RE	'O'
#define	OO	'P'
#define	AA	'Q'
#define	NEG	'R'
#define	SR	'S'
#define	MYEOF	'Z'

#define	MAXINPUT	(1024*1024)
char	input[MAXINPUT];
int	eof;
int	ipos;

char	*myname;	/* name of this command */

int	nextt;		/* next token */
int	lexnum;		/* lexical number value */
int	lexstr;		/* lexical string ipos */
int	lineno = 1;	/* current line number */

#define	STACKSIZE	64
int	objsize[STACKSIZE];
int	sp = 0;

int	highwater = 0;

#define	sym	struct _sym
sym {
	int	ipos;
	int	type;
	int	scope;
	int	base;
	int	size;
	int	dim;
} symtab[513];		/* symbol table */
int	symsp = 0;

void	expr(void);
void	decl(void);


int
isnamechar(register int t)
{
	return(((t >= '0') && (t <= '9')) ||
	       ((t >= 'A') && (t <= 'Z')) ||
	       ((t >= 'a') && (t <= 'z')) ||
	       (t == '_'));
}

char *
namestring(register int ipos)
{
	static char name[256];
	register int i = 0;

	while (isnamechar(name[i] = input[ipos+i])) ++i;
	name[i] = 0;
	return(&(name[0]));
}

int warn(fmt, a, b, c)
char *fmt;
int a, b, c;
{
	fprintf(stderr, "#line %d: ", lineno);
	fprintf(stderr, fmt, a, b, c);
	fprintf(stderr, "\n");
	return 0;
}

int error(fmt, a, b, c)
char *fmt;
int a, b, c;
{
	warn(fmt, a, b, c);
	fprintf(stderr,
"#compilation terminated on this error\n"
"</PRE>\n"
"<P>\n"
		);
	exit(0);
	return 0;
}


/*	Code generation stuff
*/

void
incsp(void)
{
	++sp;
}

void
decsp(void)
{
	--sp;
}

#define	prstr(s)	pr(s, (sizeof(s)-1))
#define	prop(s)		{ prtab(); prstr(s); prtab(); }

void
prchar(register int c)
{
	putchar(c);
}

void
prtab(void)
{
	prchar('\t');
}

void
prcomma(void)
{
	prchar(',');
}

void
prnewline(void)
{
	prchar('\n');
}

void
pr(register char *s,
register int len)
{
	while (--len >= 0) {
		prchar(*s);
		++s;
	}
}

enum {
	ZERO,	AT,	V0,	V1,	A0,	A1,	A2,	A3,
	T0,	T1,	T2,	T3,	T4,	T5,	T6,	T7,
	S0,	S1,	S2,	S3,	S4,	S5,	S6,	S7,
	T8,	T9,	K0,	K1,	GP,	SP,	FP,	RA
};

#define	TOS	(T0 + (sp-1))
#define	NOS	(T0 + (sp-2))
#define	TMP	(T0 + sp)

char	*regname[32] = {
	"0",	"at",	"v0",	"v1",	"a0",	"a1",	"a2",	"a3",
	"t0",	"t1",	"t2",	"t3",	"t4",	"t5",	"t6",	"t7",
	"s0",	"s1",	"s2",	"s3",	"s4",	"s5",	"s6",	"s7",
	"t8",	"t9",	"k0",	"k1",	"gp",	"sp",	"fp",	"ra"
};

void
prreg(register int r)
{
	register char *s = regname[r];

	prchar('$');
	while (*s) {
		prchar(*s);
		++s;
	}
}

void
prrt(register int r)
{
	prreg(r);
}

void
prrs(register int r)
{
	prreg(r);
}

void
prrd(register int r)
{
	prreg(r);
}

void
primmed(register int r)
{
	printf("%d", r);
}

void
prnum(register int n)
{
	printf("%d", n);
}

void
mips_immed(register int rt,
register int rs,
register int immed)
{
	prrt(rt);
	prcomma();
	prrs(rs);
	prcomma();
	primmed(immed);
	prnewline();
}
void
mips_offset(register int rt,
register int rs,
register int immed)
{
	prrt(rt);
	prcomma();
	prrs(rs);
	prcomma();
	prchar('_');
	prnum(immed);
	prnewline();
}

void
mips_3reg(register int rd,
register int rs,
register int rt)
{
	prrt(rd);
	prcomma();
	prrs(rs);
	prcomma();
	prrs(rt);
	prnewline();
}

void
mips_ls(register int rt,
register int immed,
register int rs)
{
	prrt(rt);
	prcomma();
	primmed(immed);
	prchar('(');
	prrs(rs);
	prchar(')');
	prnewline();
}

void
mips_lui(register int rt,
register int immed)
{
	prop("lui");
	prrs(rt);
	prcomma();
	primmed(immed);
	prnewline();
}

void
mips_addi(register int rt,
register int rs,
register int immed)
{
	prop("addi");
	mips_immed(rt, rs, immed);
}

void
mips_ori(register int rt,
register int rs,
register int immed)
{
	prop("ori");
	mips_immed(rt, rs, immed);
}

void
mips_xori(register int rt,
register int rs,
register int immed)
{
	prop("xori");
	mips_immed(rt, rs, immed);
}

void
mips_beq(register int rt,
register int rs,
register int immed)
{
	prop("beq");
	mips_offset(rt, rs, immed);
}

void
mips_bne(register int rt,
register int rs,
register int immed)
{
	prop("bne");
	mips_offset(rt, rs, immed);
}

void
mips_jr(register int r)
{
	prop("jr");
	prreg(r);
	prnewline();
}

void
mips_space(register int n)
{
	prstr("\t.space\t");
	prnum(n);
	prnewline();
}

void
mips_or(register int rd,
register int rs,
register int rt)
{
	prop("or");
	mips_3reg(rd, rs, rt);
}

void
mips_xor(register int rd,
register int rs,
register int rt)
{
	prop("xor");
	mips_3reg(rd, rs, rt);
}

void
mips_and(register int rd,
register int rs,
register int rt)
{
	prop("and");
	mips_3reg(rd, rs, rt);
}

void
mips_addu(register int rd,
register int rs,
register int rt)
{
	prop("addu");
	mips_3reg(rd, rs, rt);
}

void
mips_subu(register int rd,
register int rs,
register int rt)
{
	prop("subu");
	mips_3reg(rd, rs, rt);
}

void
mips_slt(register int rd,
register int rs,
register int rt)
{
	prop("slt");
	mips_3reg(rd, rs, rt);
}

void
mips_sltu(register int rd,
register int rs,
register int rt)
{
	prop("sltu");
	mips_3reg(rd, rs, rt);
}

void
mips_sllv(register int rd,
register int rs,
register int rt)
{
	prop("sllv");
	mips_3reg(rd, rs, rt);
}

void
mips_srav(register int rd,
register int rs,
register int rt)
{
	prop("srav");
	mips_3reg(rd, rs, rt);
}

void
mips_sw(register int rt,
register int immed,
register int rs)
{
	prop("sw");
	mips_ls(rt, immed, rs);
}

void
mips_sh(register int rt,
register int immed,
register int rs)
{
	prop("sh");
	mips_ls(rt, immed, rs);
}

void
mips_sb(register int rt,
register int immed,
register int rs)
{
	prop("sb");
	mips_ls(rt, immed, rs);
}

void
mips_lw(register int rt,
register int immed,
register int rs)
{
	prop("lw");
	mips_ls(rt, immed, rs);
}

void
mips_lh(register int rt,
register int immed,
register int rs)
{
	prop("lh");
	mips_ls(rt, immed, rs);
}

void
mips_lb(register int rt,
register int immed,
register int rs)
{
	prop("lb");
	mips_ls(rt, immed, rs);
}

void
mips_text(void)
{
	prstr("\t.text\n");
}

void
mips_data(int n)
{
	prstr("\t.data\t");
	prnum(n);
	prchar('\n');
}

void
mips_j(register char *s)
{
	prop("j");
	while (*s) {
		prchar(*s);
		++s;
	}
	prnewline();
}

void
mips_j_(register int n)
{
	prop("j");
	prchar('_');
	prnum(n);
	prnewline();
}

void
mips_jal_(register char *s)
{
	prop("jal");
	prchar('_');
	while (*s) {
		prchar(*s);
		++s;
	}
	prnewline();
}

void
mips_syscall(void)
{
	prstr("\tsyscall\n");
}

void
mips_globl(register char *s)
{
	prstr("\t.globl\t");
	while (*s) {
		prchar(*s);
		++s;
	}
	prnewline();
}

void
mips_globl_(register char *s)
{
	prstr("\t.globl\t_");
	while (*s) {
		prchar(*s);
		++s;
	}
	prnewline();
}

void
mips_label(register char *s)
{
	while (*s) {
		prchar(*s);
		++s;
	}
	prstr(":\n");
}

void
mips_label_(register int n)
{
	prchar('_');
	prnum(n);
	prstr(":\n");
}

void
mips_prelabel(register char *s)
{
	prchar('_');
	while (*s) {
		prchar(*s);
		++s;
	}
	prstr(":\n");
}

void
pushnum(register int n)
{
	incsp();

	/* Try to optimize immediate handling...
	   ori immediate doesn't sign extend,
	   addi immediate does
	*/
	if ((n & 0xffff8000) == 0xffff8000) {
		mips_addi(TOS, 0, n);
	} else if ((n & 0xffff0000) == 0) {
		mips_ori(TOS, 0, n);
	} else if ((n & 0x0000ffff) == 0) {
		mips_lui(TOS, ((n >> 16) & 0xffff));
	} else {
		mips_lui(TOS, ((n >> 16) & 0xffff));
		mips_ori(TOS, TOS, (n & 0xffff));
	}

	objsize[sp-1] = 0;
}

void
pushgpoff(register int off)
{
	incsp();
	mips_addi(TOS, GP, off);
	objsize[sp-1] = 0;
}

void
pushfpoff(register int off)
{
	incsp();
	mips_addi(TOS, FP, off);
	objsize[sp-1] = 0;
}

void
pushdup(void)
{
	incsp();
	mips_or(TOS, NOS, 0);
	objsize[sp-1] = objsize[sp-2];
}

void
pusharg(register int argno)
{
	incsp();
	mips_or(TOS, (A0 + argno), 0);
	objsize[sp-1] = 0;
}

void
lval(register int size)
{
	objsize[sp-1] = size;
}

void
loadtos(void)
{
	/* Need both TOS loaded from memory? */

	switch (objsize[sp-1]) {
	case 0:	return;
	case 1: mips_lb(TOS, 0, TOS); break;
	case 2: mips_lh(TOS, 0, TOS); break;
	case 4: mips_lw(TOS, 0, TOS); break;
	default:
		error("cannot load %d-byte object",
		      objsize[sp-1]);
	}

	objsize[sp-1] = 0;
}

void
loadnostos(void)
{
	/* Need either NOS or TOS loaded from memory? */

	decsp();
	loadtos();
	incsp();
	loadtos();
}

void
loadnos(void)
{
	/* Need NOS loaded from memory? */

	decsp();
	loadtos();
	incsp();
}

void
setarg(register int argno)
{
	loadtos();
	mips_or((A0 + argno), TOS, 0);
	decsp();
}

void
pushop(register int op)
{
	switch (op) {
	case NEG:
		loadtos();
		mips_subu(TOS, 0, TOS);
		break;
	case '!':
		loadtos();
		mips_sltu(TOS, 0, TOS);
		break;
	case '~':
		loadtos();
		mips_xori(TOS, TOS, -1);
		break;
	case MULBY4:
		loadtos();
		mips_addu(TOS, TOS, TOS);
		mips_addu(TOS, TOS, TOS);
		break;
	case MULBY2:
		loadtos();
		mips_addu(TOS, TOS, TOS);
		break;
	case AFP:
		loadtos();
		mips_addu(TOS, TOS, FP);
		break;
	case ASP:
		loadtos();
		mips_addu(TOS, TOS, SP);
		break;
	case AGP:
		loadtos();
		mips_addu(TOS, TOS, GP);
		break;
	case RETVAL:
		loadtos();
		mips_or(V0, TOS, 0);
		decsp();
		break;
	case '+':
		loadnostos();
		mips_addu(NOS, NOS, TOS);
		decsp();
		break;
	case '-':
		loadnostos();
		mips_subu(NOS, NOS, TOS);
		decsp();
		break;
	case SL:
		loadnostos();
		mips_sllv(NOS, NOS, TOS);
		decsp();
		break;
	case SR:
		loadnostos();
		mips_srav(NOS, NOS, TOS);
		decsp();
		break;
	case LE:
		loadnostos();
		mips_slt(TMP, TOS, NOS);	/* GT */
		mips_slt(NOS, NOS, TOS);	/* LT */
		mips_or(TMP, NOS, TMP);		/* NE */
		mips_xori(TMP, TMP, 1);		/* EQ */
		mips_or(NOS, NOS, TMP);
		decsp();
		break;
	case '<':
		loadnostos();
		mips_slt(NOS, NOS, TOS);
		decsp();
		break;
	case GE:
		loadnostos();
		mips_slt(TMP, NOS, TOS);	/* LT */
		mips_slt(NOS, TOS, NOS);	/* GT */
		mips_or(TMP, NOS, TMP);		/* NE */
		mips_xori(TMP, TMP, 1);		/* EQ */
		mips_or(NOS, NOS, TMP);
		decsp();
		break;
	case '>':
		loadnostos();
		mips_slt(NOS, TOS, NOS);
		decsp();
		break;
	case EQ:
		loadnostos();
		mips_xor(NOS, NOS, TOS);	/* NE */
		mips_sltu(NOS, 0, NOS);
		mips_xori(TMP, TMP, 1);
		decsp();
		break;
	case NE:
		loadnostos();
		mips_xor(NOS, NOS, TOS);	/* NE */
		mips_sltu(NOS, 0, NOS);
		decsp();
		break;
	case '&':
		loadnostos();
		mips_and(NOS, NOS, TOS);
		decsp();
		break;
	case '^':
		loadnostos();
		mips_xor(NOS, NOS, TOS);
		decsp();
		break;
	case '|':
		loadnostos();
		mips_or(NOS, NOS, TOS);
		decsp();
		break;
	default:
		error("cannot yet handle op (%c)", op);
	}
}

void
store(register int prop)
{
	/* Store TOS into NOS */

	loadtos();
	switch (objsize[sp-2]) {
	case 0: error("lvalue required");
	case 1: mips_sb(TOS, 0, NOS); break;
	case 2: mips_sh(TOS, 0, NOS); break;
	case 4: mips_sw(TOS, 0, NOS); break;
	default:
		error("cannot store %d-byte object",
		      objsize[sp-2]);
	}

	if (prop) {
		/* Just in case we have x=(y=z)...
		   Strictly speaking, x=(y=z) sets x=((typeof(y))z),
		   but I don't think we have to be that precise here
		*/
		mips_or(NOS, TOS, 0);
		decsp();
		objsize[sp-1] = 0;
	} else {
		decsp();
		decsp();
	}
}

void
jump(register int a)
{
	/* Compiler-generated labels are nearby...
	   so use a branch instead
	*/

	mips_j_(a);
}

void
jumpf(register int a)
{
	loadtos();
	mips_beq(TOS, 0, a);
	decsp();
}

void
jumpt(register int a)
{
	loadtos();
	mips_bne(TOS, 0, a);
	decsp();
}

void
label(register int a)
{
	mips_label_(a);
}

void
ghoto(register char *s)
{
	mips_j(s);
}

void
target(register char *s)
{
	mips_prelabel(s);
}

void
startup(void)
{
	mips_text();
	mips_globl("main");
	mips_globl_("exit");
	mips_globl_("print_int");
	mips_globl_("print_string");
	mips_label("main");
	mips_lui(GP, ((DATABASE >> 16) & 0xffff));
	mips_jal_("main");
	mips_label("_exit");
	mips_ori(V0, 0, 10);
	mips_syscall();
	mips_label("_print_int");
	mips_ori(V0, 0, 1);
	mips_syscall();
	mips_jr(RA);
	mips_label("_print_string");
	mips_ori(V0, 0, 4);
	mips_syscall();
	mips_jr(RA);
}

void
call(register int mysym)
{
	register char *n = namestring(symtab[mysym].ipos);
	register int i;

	/* We're not a leaf procedure.... */
	isleaf = 0;

	/* Save registers */
	if (sp > 0) {
		mips_addi(SP, SP, -4*(TOS-T0+1));
		for (i=T0; i<=TOS; ++i) {
			mips_sw(i, -4*(i-T0), SP);
		}
	}

	/* Call the function */
	mips_jal_(n);

	/* Restore registers */
	if (sp > 0) {
		for (i=T0; i<=TOS; ++i) {
			mips_lw(i, -4*(i-T0), SP);
		}
		mips_addi(SP, SP, 4*(TOS-T0+1));
	}

	/* Copy the return value to someplace useful */
	incsp();
	mips_or(TOS, V0, 0);
	objsize[sp-1] = 0;
}


void
funcbegin(register int mysym)
{
	register char *n = namestring(symtab[mysym].ipos);

	fpoffset = -4;
	highwater = 0;
	beginlab = labnum++;
	endlab = labnum++;

	/* For now, functions always return an int */
	symtab[mysym].type = FUNC;
	symtab[mysym].base = -4;
	symtab[mysym].size = 4;
	symtab[mysym].dim = 1;

	++scope;

	/* So far, we could be a leaf procedure.... */
	isleaf = 1;

	mips_text();
	mips_globl_(n);
	label(beginlab);
}


void
funcend(register int mysym)
{
	register char *n = namestring(symtab[mysym].ipos);

	/* For now, functions always return an int */
	symtab[mysym].type = FUNC;
	symtab[mysym].base = -4;
	symtab[mysym].size = 4;
	symtab[mysym].dim = 1;

	/* Now the common end return code...
	   but special-case leaf procedures
	*/
	if ((isleaf == 0) || (highwater != 0)) {
		/* Not a leaf; do full stack frame...
		   Stack looks like:
		   [old fp] [ret addr] [locals]
		   we do this here because that's when we know
		   how much space we need for locals...
		*/

		/* Add space for fp and return address */
		highwater += 8;	

		label(endlab);
		mips_lw(RA, -4, FP);		/* ra = fp[-4] */
		mips_or(SP, FP, 0);		/* sp = fp */
		mips_lw(FP, 0, SP);		/* fp = old fp */
		mips_addi(SP, SP, 4);		/* sp = old sp */
		mips_jr(RA);			/* return */
		mips_prelabel(n);
		mips_addi(SP, SP, -highwater);	/* sp -= highwater */
		mips_sw(FP, highwater-4, SP);	/* sp[highwater-4] = fp */
		mips_addi(FP, SP, highwater-4);	/* fp = &(sp[highwater-4]) */
		mips_sw(RA, -4, FP);		/* fp[-4] = ra */
	} else {
		/* A leaf without locals... */

		label(endlab);
		mips_jr(RA);			/* return */
		mips_prelabel(n);
	}

	jump(beginlab);

	--scope;
}

void
def(register int mysym)
{
	register char *n = namestring(symtab[mysym].ipos);
	register int asize;

	/* Objects always are 4-byte word alligned... */
	asize = (((symtab[mysym].size * symtab[mysym].dim) + 3) & ~3);

	symtab[mysym].type = VAR;
	if ((symtab[mysym].scope = scope) == 0) {
		/* Offset from $gp */
		symtab[mysym].base = gpoffset;
		gpoffset += asize;

		mips_data(DATABASE + symtab[mysym].base);
		mips_globl(n);
		mips_label(n);
		mips_space(asize);
	} else {
		/* Offset from $fp */
		fpoffset -= asize;
		symtab[mysym].base = fpoffset;

		if (highwater < -fpoffset) {
			highwater = -fpoffset;
		}
	}
}


int
defstr(register int spos)
{
	register int num;
	register int asize;

	mips_data(DATABASE + gpoffset);

	asize = 0;
	while (input[++spos] != '"') {
		if (++asize > 1) {
			if ((asize & 7) == 1) {
				prnewline();
				prstr("\t.byte\t");
			} else {
				prstr(", ");
			}
		} else {
			prstr("\t.byte\t");
		}
		if (input[spos] == '\\') {
			switch (input[++spos]) {
			case 't':	printf("%3d", '\t'); break;
			case 'n':	printf("%3d", '\n'); break;
			case 'r':	printf("%3d", '\r'); break;
			case 'b':	printf("%3d", '\b'); break;
			case '0':	case '1':	case '2':
			case '3':	case '4':	case '5':
			case '6':	case '7':
				num = (input[spos] - '0');
				while ((input[spos+1] >= '0') &&
				       (input[spos+1] <= '7')) {
					num *= 8;
					num += (input[++spos] - '0');
				}
				printf("%3d", num);
				break;
			default:
				printf("%3d", input[spos]);
			}
		} else {
			printf("%3d", input[spos]);
		}
	}

	++asize;
	printf("\n"
	       "\t.byte\t0\n"
	       "\n"
	       "\t.text\n");

	/* Make size a multiple of 4 bytes for allignment... */
	asize = ((asize + 3) & ~3);
	gpoffset += asize;
	return(DATABASE + gpoffset - asize);
}



/*	Lexicals...
*/

int
prefixis(register char *p)
{
	register int i = 0;

	for (;;) {
		register int t = p[i];

		if (t == 0) {
			ipos += i;
			return(1);
		}
		if (t != input[ipos + i]) {
			return(0);
		}
		++i;
	}
}

int
nameis(register char *p)
{
	register int i = 0;

	for (;;) {
		register int t = p[i];

		if (!isnamechar(t)) {
			if (!isnamechar(input[ipos + i])) {
				ipos += i;
				return(1);
			} else {
				return(0);
			}
		}
		if (t != input[ipos + i]) {
			return(0);
		}
		++i;
	}
}

int
lexhelp(void)
{
	register int base = 10;

again:

	/* Recognize all the non-name stuff */
	switch (input[ipos]) {

	/* Handle whitespace, etc. */
	case '\n':
#ifdef	NOTNOW
		printf("#line\t%d:\t", lineno);
		while (linestart <= ipos) {
			putchar(input[linestart]);
			++linestart;
		}
#endif
		++lineno;
		/* Fall through... */
	case ' ':	case '\t':	case '\r':
		++ipos;
		goto again;
	case '\000':
		return(MYEOF);

	/* Handling of punctuation... */
	case '=':	case '!':
	case '<':	case '>':
	case '+':	case '-':	case '~':
	case '*':	case '/':	case '%':
	case '|':	case '&':
		if (prefixis("==")) return(EQ);
		if (prefixis("!=")) return(NE);
		if (prefixis(">=")) return(GE);
		if (prefixis("<=")) return(LE);
		if (prefixis("<<")) return(SL);
		if (prefixis("++")) return(PP);
		if (prefixis("--")) return(MM);
		if (prefixis("|=")) return(OE);
		if (prefixis("^=")) return(XE);
		if (prefixis("&=")) return(AE);
		if (prefixis("+=")) return(PE);
		if (prefixis("-=")) return(ME);
		if (prefixis("*=")) return(TE);
		if (prefixis("/=")) return(DE);
		if (prefixis("%=")) return(RE);
		if (prefixis("||")) return(OO);
		if (prefixis("&&")) return(AA);
		/* Fall through... */
	case ',':	case '?':	case ':':
	case '{':	case '}':	case '^':
	case '[':	case ']':
	case '(':	case ')':
	case ';':
		return(input[ipos++]);

	/* Handling of numbers... */
	case '0':
		base = 8;
		switch (input[++ipos]) {
		case 'b': base = 2; ++ipos; break;
		case 'x': base = 16; ++ipos; break;
		}
	case '1':	case '2':	case '3':
	case '4':	case '5':	case '6':
	case '7':	case '8':	case '9':
		lexnum = 0;
		for (;;) {
			register int t = input[ipos];

			if ((t >= '0') && (t <= '9')) {
				t -= '0';
			} else if (((t |= ('a'-'A')) >= 'a') &&
				   (t <= 'f')) {
				t -= ('a' - 10);
			} else {
				return(NUM);
			}

			if (t >= base) {
				error("invalid digit");
			}

			lexnum = (lexnum * base) + t;
			++ipos;
		}
	case '\'':
		++ipos;
		lexnum = input[ipos++];
		if (input[ipos++] != '\'') {
			error("ill-formed character constant");
		}
		return(NUM);
	case '"':
		lexstr = ipos;
		do {
			++ipos;
			if (input[ipos] == 0) {
				error("string ends in end of input");
			}
		} while ((input[ipos] != '"') ||
			 (input[ipos-1] == '\\'));
		++ipos;
		return(STRING);
	default:
		if (!isnamechar(input[ipos])) {
			error("illegal character 0x%02x (%c)",
			      input[ipos],
			      input[ipos]);
			++ipos;
			goto again;
		}
	}

	/* Must be a name... */
	if (nameis("int")) return(INT);
	if (nameis("short")) return(SHORT);
	if (nameis("char")) return(CHAR);
	if (nameis("if")) return(IF);
	if (nameis("else")) return(ELSE);
	if (nameis("while")) return(WHILE);
	if (nameis("do")) return(DO);
	if (nameis("return")) return(RETURN);
	if (nameis("for")) return(FOR);
	if (nameis("goto")) return(GOTO);

	/* Find it in the symbol table */
	for (lexsym=(symsp-1); lexsym>=0; --lexsym) {
		if (nameis(&(input[symtab[lexsym].ipos]))) {
			return(symtab[lexsym].type);
		}
	}

	/* Make a new symbol table entry */
	symtab[lexsym = (symsp++)].ipos = ipos;
	nameis(&(input[ipos]));
	return(symtab[lexsym].type = ((input[ipos] == ':') ?
				      TARGET :
				      WORD));
}

int
lex(void)
{
	nextt = lexhelp();
	return(nextt);
}

int
match(register int t)
{
	if (nextt == t) {
		lex();
		return(1);
	}
	return(0);
}

int
assume(register int t)
{
	if (!match(t)) {
		warn("missing %c assumed", t);
		return(0);
	}
	return(1);
}



/*	Parsing...
*/

void
memaddr(register int mysym)
{
	/* Base address */
	if (symtab[mysym].scope != 0) {
		pushfpoff(symtab[mysym].base);
	} else {
		pushgpoff(symtab[mysym].base);
	}

	lex();
	if (match('[')) {
		/* subscripted */
		expr();		/* Index value */
		assume(']');

		/* Multiply by element size */
		switch (symtab[mysym].size) {
		case 2:	pushop(MULBY2); break;
		case 1: break;
		default:
			pushop(MULBY4);
		}

		pushop('+');	/* Add to base address */
	}

	lval(symtab[mysym].size);
}

void
unary(void)
{
	register int mysym;
	register int args = 0;

	switch (nextt) {
	case PP:
		lex();
		unary();
		pushdup();
		pushnum(1);
		pushop('+');
		store(1);
		break;
	case MM:
		lex();
		unary();
		pushdup();
		pushnum(-1);
		pushop('+');
		store(1);
		break;
	case '(':
		lex();
		expr();
		assume(')');
		break;
	case '-':
		lex();
		unary();
		pushop(NEG);
		break;
	case '!':
		lex();
		unary();
		pushop('!');
		break;
	case '~':
		lex();
		unary();
		pushop('~');
		break;
	case VAR:
		memaddr(lexsym);
		break;
	case WORD:
		symtab[lexsym].type = FUNC;
		symtab[lexsym].base = 0;
		/* Fall through... */
	case FUNC:
		/* Function call */
		mysym = lexsym;
		lex();
		if (!match('(')) {
			error("undefined variable %s",
			      namestring(symtab[mysym].ipos));
		}
		args = 0;
		while (!match(')')) {
			expr();
			setarg(args++);
			match(',');
		}
		call(mysym);
		break;
	case NUM:
		pushnum(lexnum);
		lex();
		break;
	case STRING:
		pushnum(defstr(lexstr));
		lex();
		break;
	default:
		error("malformed expression");
	}

	/* Suffix operation */
	switch (nextt) {
	case PP:
		lex();
		pushdup();
		loadnos();
		pushdup();
		pushnum(1);
		pushop('+');
		store(0);
		break;
	case MM:
		lex();
		pushdup();
		loadnos();
		pushdup();
		pushnum(1);
		pushop('+');
		store(0);
		break;
	}
}

void
mul(void)
{
	register int t;

	unary();
	for (;;) {
		switch (nextt) {
		case '*':
		case '/':
		case '%':
			t = nextt;
			lex();
			unary();
			pushop(t);
		default:
			return;
		}
	}
}

void
add(void)
{
	register int t;

	mul();
	for (;;) {
		switch (nextt) {
		case '+':
		case '-':
			t = nextt;
			lex();
			mul();
			pushop(t);
		default:
			return;
		}
	}
}

void
slsr(void)
{
	register int t;

	add();
	for (;;) {
		switch (nextt) {
		case SL:
		case SR:
			t = nextt;
			lex();
			add();
			pushop(t);
		default:
			return;
		}
	}
}

void
leltgegt(void)
{
	register int t;

	slsr();
	for (;;) {
		switch (nextt) {
		case LE:
		case '<':
		case GE:
		case '>':
			t = nextt;
			lex();
			slsr();
			pushop(t);
		default:
			return;
		}
	}
}

void
eqne(void)
{
	register int t;

	leltgegt();
	for (;;) {
		switch (nextt) {
		case EQ:
		case NE:
			t = nextt;
			lex();
			leltgegt();
			pushop(t);
		default:
			return;
		}
	}
}

void
and(void)
{
	eqne();
	while (match('&')) {
		eqne();
		pushop('&');
	}
}

void
xor(void)
{
	and();
	while (match('^')) {
		and();
		pushop('^');
	}
}

void
or(void)
{
	xor();
	while (match('|')) {
		xor();
		pushop('|');
	}
}

void
andand(void)
{
	register int lab;

	or();
	if (match(AA)) {
		lab = labnum;
		labnum += 3;

		do {
			jumpf(lab);
			++labnum;
			or();
		} while (match(AA));

		jumpt(lab+1);
		label(lab);
		pushnum(0);
		decsp();
		jump(lab+2);
		label(lab+1);
		pushnum(1);
		label(lab+2);
	}
}

void
oror(void)
{
	register int lab;

	andand();
	if (match(OO)) {
		lab = labnum;
		labnum += 3;

		do {
			jumpt(lab);
			++labnum;
			andand();
		} while (match(OO));

		jumpf(lab+1);
		label(lab);
		pushnum(1);
		decsp();
		jump(lab+2);
		label(lab+1);
		pushnum(0);
		label(lab+2);
	}
}

void
cond(void)
{
	register int lab;

	oror();
	if (match('?')) {
		lab = labnum;
		labnum += 2;

		jumpf(lab);
		expr();
		decsp();
		jump(lab+1);
		assume(':');
		label(lab);
		cond();
		label(lab+1);
	}
}

void
assign(void)
{
	register int t;

	cond();
	switch (nextt) {
	case '=':
		lex();
		assign();
		store(1);
		break;
	case OE:
		lex();
		pushdup();
		assign();
		pushop('|');
		store(1);
		break;
	case XE:
		lex();
		pushdup();
		assign();
		pushop('^');
		store(1);
		break;
	case AE:
		lex();
		pushdup();
		assign();
		pushop('&');
		store(1);
		break;
	case PE:
		lex();
		pushdup();
		assign();
		pushop('+');
		store(1);
		break;
	case ME:
		lex();
		pushdup();
		assign();
		pushop('-');
		store(1);
		break;
	case TE:
		lex();
		pushdup();
		assign();
		pushop('*');
		store(1);
		break;
	case DE:
		lex();
		pushdup();
		assign();
		pushop('/');
		store(1);
		break;
	case RE:
		lex();
		pushdup();
		assign();
		pushop('%');
		store(1);
		break;
	}
}

void
expr(void)
{
	assign();
	while (match(',')) {
		decsp();
		assign();
	}
}

int
newsym(void)
{
	/* Create a new symbol table entry */
	register int mysym;

	switch (nextt) {
	case WORD:
		mysym = lexsym;
		break;
	case VAR:
	case FUNC:
		if (scope == symtab[lexsym].scope) {
			warn("redefinition of identifier");
		}
		symtab[mysym = (symsp++)].ipos = symtab[lexsym].ipos;
		break;
	default:
		error("ill-formed declaration of %s",
		      namestring(symtab[mysym].ipos));
	}
	lex();
	symtab[mysym].scope = scope;
	return(mysym);
}

void
stat(void)
{
	register int scopesymsp, scopeoffset;
	register int lab;
	register int mysym;

	switch (nextt) {
	case '{':
		lex();
		scopesymsp = symsp;
		scopeoffset = fpoffset;

		decl();
		while (!match('}')) {
			stat();
		}

		symsp = scopesymsp;
		fpoffset = scopeoffset;
		break;
	case IF:
		lex();
		expr();
		lab = labnum;
		labnum += 2;
		jumpf(lab);
		stat();
		if (nextt == ELSE) {
			lex();
			jump(lab+1);
			label(lab);
			stat();
			label(lab+1);
		} else {
			label(lab);
		}
		break;
	case FOR:
		lex();
		assume('(');
		lab = labnum;
		labnum += 4;
		if (!match(';')) {
			expr();
			decsp();
			match(';');
		}
		label(lab);
		if (!match(';')) {
			expr();
			jumpf(lab+1);
			match(';');
		}
		jump(lab+2);
		label(lab+3);
		if (!match(')')) {
			expr();
			decsp();
			match(')');
		}
		jump(lab);
		label(lab+2);
		stat();
		jump(lab+3);
		label(lab+1);
		break;
	case WHILE:
		lex();
		lab = labnum;
		labnum += 2;
		label(lab);
		expr();
		jumpf(lab+1);
		stat();
		jump(lab);
		label(lab+1);
		break;
	case DO:
		lex();
		lab = (labnum++);
		label(lab);
		stat();
		if (match(WHILE)) {
			error("do missing while");
		}
		expr();
		assume(';');
		jumpt(lab);
		break;
	case RETURN:
		lex();
		if (nextt != ';') {
			expr();
			pushop(RETVAL);
		}
		match(';');
		break;
	case GOTO:
		lex();
		ghoto(namestring(symtab[newsym()].ipos));
		--symsp;
		break;
	case TARGET:
		target(namestring(symtab[symsp-1].ipos));
		--symsp;
		lex();
		assume(':');
		break;
	case ';':
		lex();
		break;
	default:
		expr();
		assume(';');
		decsp();
		break;
	}
}

int
ctype(void)
{
	switch (nextt) {
	case INT:	lex(); return(4);
	case SHORT:	lex(); return(2);
	case CHAR:	lex(); return(1);
	case WORD:	if (scope == 0) {
				warn("missing int keyword assumed");
				return(4);
			}
	}
	return(0);
}

void
decl(void)
{
	register int scopeoffset;
	register int mysym, argsym;
	register int size, args;

	while ((size = ctype()) != 0) {
moredecls:
		mysym = newsym();
		symtab[mysym].size = size;

		switch (nextt) {
		case '[':
			lex();
			symtab[mysym].type = VAR;
			if (nextt != NUM) {
				error("non-constant dim for %s",
				      namestring(symtab[mysym].ipos));
			}
			symtab[mysym].dim = lexnum;
			def(mysym);
			lex();
			assume(']');
			if (match(',')) goto moredecls;
			assume(';');
			break;
		case ';':
			symtab[mysym].dim = 1;
			def(mysym);
			lex();
			break;
		case ',':
			symtab[mysym].dim = 1;
			def(mysym);
			lex();
			goto moredecls;
		case '(':
			if (scope != 0) {
				error("nested definition of function %s",
				      namestring(symtab[mysym].ipos));
			}
			lex();

			funcbegin(mysym);

			args = 0;
			while ((size = ctype()) != 0) {
				argsym = newsym();
				symtab[argsym].type = VAR;
				symtab[argsym].size = 4;
				symtab[argsym].dim = 1;
				def(argsym);

				/* Copy arg from register to local */
				pushnum(symtab[argsym].base);
				pushop(AFP);
				lval(4);
				pusharg(args++);
				store(0);

				if (match('[')) {
					error("array arguments currently not supported");
				}
				match(',');
			}
			if (!match(')')) {
				warn("missing ) in function argument declaration");
			}
			stat();
			funcend(mysym);

			break;
		default:
			error("declaration missing ; or argument list");
		}
	}
}

int
main(int argc, char **argv)
{
	int c;
	FILE * pFile;
	long lSize;
	char * buffer;
	size_t result;
	
	eof = 0;
	if ( argc == 0x2 )
	{	pFile = fopen ( argv[argc - 1], "r" );
		if (pFile==NULL) {fputs ("File error",stderr); exit (1);}
		// obtain file size:
		fseek (pFile , 0 , SEEK_END);
		lSize = ftell (pFile);
		rewind (pFile);

		// copy the file into the buffer:
		result = fread (input,1,lSize,pFile);
		if (result != lSize) {fputs ("Reading error",stderr); exit (3);}
		eof = lSize;
	} else
	{	while ((c = getchar()) != EOF) input[eof++] = c;
	};

	input[eof] = 0;
	ipos = 0;
	nextt = lex();
	startup();
	decl();
}
