# What

The source code in this project is Minix 3.1.0. It is extracted from the accompanying CD-ROM in the textbook `Operating Systems Design and Implementation 3rd edition`.

# Where

To acquire the CD-ROM ISO, you could

- either purchase the book
- or go to [minix3.org](http://minix3.org) and [download the ISO](http://download.minix3.org/iso/minix-3.1.0-book.iso.bz2)
 
# How

You can install minix3 in Bochs or QEMU. But I found that the networking works out-of-the-box in the latest QEMU. Here are the steps.

## Step 1 Create HD image

```
qemu-img create minix3.img 8G
```

## Step 2 Install

The ISO file `minix3.cdr` is ripped from CD-ROM in Mac OS disk utility.`

```
qemu-system-i386 \
 -net user \
 -net nic \ 
 -m 1024 \
 -cdrom minix3.cdr \
 -drive file=minix3.img,index=0,media=disk,format=raw \
 -boot d
```

## Step 3 Enable Networking

First, during installation, choose NE2K ethernet card.


Secondly, modify /usr/etc/rc.local and change address and IRQ.

```
dp8390_arg='DPETH0=300:3'
```

## Step 4 Run

We use slirp in QEMU. It is NAT. We portforward telent and ftp to the host port `20023` and `20021`. 

```
qemu-system-i386 \
    -drive file=minix3.img,format=raw,media=disk,index=0 \
    -netdev user,id=net0,hostfwd=tcp::20023-:23,hostfwd=tcp::20021-:21 \
    -device ne2k_isa,netdev=net0,irq=3,iobase=0x300 \
    -m 64 \
    -no-reboot  \
    -rtc base=localtime \
    -k en-us
```

## Step 5 Connect from the host


- Telent

```
gtelnet localhost 20023
```

Choose terminal type `minix`. You can find more by `man 5 termcap`


## Step 6 Compile kernel + user space => image

- 10 cores M1 Max Mac Studio takes `1:37.95`

```
cd /usr/src/tools
make clean
time make images

...
    text     data      bss      size
    19568     3144    29808     52520  ../kernel/kernel
    19504     2360    48616     70480  ../servers/pm/pm
    42624     5556  5316124   5364304  ../servers/fs/fs
     4352      616     4696      9664  ../servers/rs/rs
    26144     4996    44192     75332  ../drivers/tty/tty
     4784      764     3012      8560  ../drivers/memory/memory
     5904      504    63276     69684  ../drivers/log/log
    23680    10776    10932     45388  AT:../drivers/at_wini/at_wini
    11328     1944     7276     20548  BIOS:../drivers/bios_wini/bios_wini
    10352     1480     4144     15976  FLOPPY:../drivers/floppy/floppy
     7088     2284     1356     10728  ../servers/init/init
   ------   ------   ------   -------
   175328    34424  5533432   5743184  total
    1:21.75 real      37.51 user      27.26 sys

make hdboot
```
- 10 cores M1 PRO 16 inch Macbook pro takes `1:31.05`

```
…
     text     data      bss      size
    19568     3144    29808     52520  ../kernel/kernel
    19504     2360    48616     70480  ../servers/pm/pm
    42624     5556  5316124   5364304  ../servers/fs/fs
     4352      616     4696      9664  ../servers/rs/rs
    26144     4996    44192     75332  ../drivers/tty/tty
     4784      764     3012      8560  ../drivers/memory/memory
     5904      504    63276     69684  ../drivers/log/log
    23680    10776    10932     45388  AT:../drivers/at_wini/at_wini
    11328     1944     7276     20548  BIOS:../drivers/bios_wini/bios_wini
    10352     1480     4144     15976  FLOPPY:../drivers/floppy/floppy
     7088     2284     1356     10728  ../servers/init/init
   ------   ------   ------   -------
   175328    34424  5533432   5743184  total
    1:31.05 real      50.23 user      35.50 sys
```

By using kvm acceleartion in QEMU, quad-core Intel(R) Xeon(R) CPU E3-1225 v5 @ 3.30GHz takes `5.36` seconds.

```
…
     text     data      bss      size
    19568     3144    29808     52520  ../kernel/kernel
    19504     2360    48616     70480  ../servers/pm/pm
    42624     5556  5316124   5364304  ../servers/fs/fs
     4352      616     4696      9664  ../servers/rs/rs
    26144     4996    44192     75332  ../drivers/tty/tty
     4784      764     3012      8560  ../drivers/memory/memory
     5904      504    63276     69684  ../drivers/log/log
    23680    10776    10932     45388  AT:../drivers/at_wini/at_wini
    11328     1944     7276     20548  BIOS:../drivers/bios_wini/bios_wini
    10352     1480     4144     15976  FLOPPY:../drivers/floppy/floppy
     7088     2284     1356     10728  ../servers/init/init
   ------   ------   ------   -------
   175328    34424  5533432   5743184  total
       5.36 real       0.78 user       3.31 sys
```






