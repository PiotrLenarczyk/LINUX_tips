#!/bin/bash
#https://superuser.com/questions/332252/how-to-create-and-format-a-partition-using-a-bash-script

echo "===="
echo -e "\tThis script could damage stored data!"
echo "===="

DEVICE=/dev/null
sed -e 's/\s*\([\+0-9a-zA-Z]*\).*/\1/' << EOF | fdisk $DEVICE
  o # clear the in memory partition table
  n # new partition
  p # primary partition
  1 # partition number 1
    # default - start at beginning of disk 
  +2M # first parttion size
  n # new partition
  p # primary partition
  2 # partition number 
    # default
  +80M # second partition size
  n # new partition
  p # primary partition
  3 # partion number
    # default, start immediately after preceding partition
    # default, extend partition to end of disk
  a # make a partition bootable
  2 # bootable partition no
  p # print the in-memory partition table
  w # write the partition table
  q # and we're done
 EOF
