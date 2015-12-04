#SETUP
Required software:
lib32stdc++6
sdcc (3.5.0)
stm8flash

lib32stdc++6 can be install with apt

some distros may not have the latest gnu toolchain, can upgrade ubuntu with the following:
sudo apt-get install libstdc++6
sudo add-apt-repository ppa:ubuntu-toolchain-r/test 
sudo apt-get update
sudo apt-get upgrade
sudo apt-get dist-upgrade

sdcc can be obtained from their page on sourceforge

stm8flash is a git repository courtesy of someone named valentin i think, get it, add to path
might require apt-get install libusb-1.0
then make and make install


stm8flash -c stlink -p stm8l051f3 -w test.ihx

sdcc -mstm8 --std-c99 test.c

problems with connecting to programmers:
/etc/udev/rules.d/stmicro.rules   << ATTRS{idVendor}=="0483", MODE:="0666"


PLEASE SEE THE IR_FINAL DIRECTORY FOR THE README FOR THE CODE
