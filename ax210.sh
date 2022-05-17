#!/bin/bash
sudo make defconfig-iwlwifi-public
sudo make -j16
sudo make install
sudo cp iwlwifi-ty-a0-gf-a0-59.ucode /lib/firmware/
sudo reboot
