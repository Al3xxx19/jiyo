# Jiyo Core

## Setup

[Jiyo Core](https://jiyo.cloud/wallet) is the original Jiyo client and it builds the backbone of the network. However, it downloads and stores the entire history of Jiyo transactions; depending on the speed of your computer and network connection, the synchronization process can take anywhere from a few hours to a day or more. Thankfully you only have to do this once.

## Running

The following are some helpful notes on how to run Jiyo on your native platform.

### Linux

Download appropriate files for your architecture:

* jiyo-<version>-aarch64.tar.gz (64-bit A64 ARMv8-A)
* jiyo-<version>-armhf.tar.gz (32-bit ARMv7 hard-float ABI)
* jiyo-<version>-lin32.tar.gz (32-bit x86)
* jiyo-<version>-lin64.tar.gz (64-bit x86)

Unpack the files into a directory and run:

* usr/bin/jiyo-qt (GUI) or usr/bin/jiyod (headless)

### Windows

Download appropriate files for your architecture:

* jiyo-<version>-win32.tar.gz (32-bit x86 portable version)
* jiyo-<version>-win64.tar.gz (64-bit x86 portable version)
* jiyo-<version>-win32-setup-unsigned.exe (32-bit x86 installer version)
* jiyo-<version>-win64-setup-unsigned.exe (64-bit x86 installer version)

Unpack the files into a directory and run:

* usr/bin/jiyo-qt.exe (GUI) or usr/bin/jiyod.exe (headless)

or run installer and launch from windows menu.

### OSX

Download appropriate files for your architecture:

* jiyo-<version>-osx64.tar.gz (portable version)
* jiyo-<version>-osx64-unsigned.dmg (disk image version)

Unpack the files into a directory and run:

* usr/bin/jiyo-qt (GUI) or usr/bin/jiyod (headless)

or drag Jiyo-Qt to your applications folder and then run Jiyo-Qt.

### Help

* Ask for help on [BitcoinTalk](https://bitcointalk.org/index.php?topic=4238243)
* Join our Discord server [Discord Server](https://discord.jiyo.cloud)

# Building

The following are developer notes on how to build Jiyo on your native platform. They are not complete guides, but include notes on the necessary libraries, compile flags, etc.

* [OSX Build Notes](build-osx.md)
* [Unix Build Notes](build-unix.md)
* [Gitian Building Guide](gitian-building.md)

# Development

The Jiyo repo's [root README](https://github.com/Jiyo-Project/jiyo/blob/master/README.md) contains relevant information on the development process and automated testing.

* [Developer Notes](developer-notes.md)
* [Multiwallet Qt Development](multiwallet-qt.md)
* [Release Notes](release-notes.md)
* [Release Process](release-process.md)
* [Unit Tests](unit-tests.md)
* [Unauthenticated REST Interface](REST-interface.md)
* [Dnsseed Policy](dnsseed-policy.md)

### Resources

* Discuss on the [BitcoinTalk](https://bitcointalk.org/index.php?topic=4238243) forum.

### Miscellaneous

* [Assets Attribution](assets-attribution.md)
* [Files](files.md)
* [Tor Support](tor.md)
* [Init Scripts (systemd/upstart/openrc)](init.md)

# License

Distributed under the [MIT/X11 software license](http://www.opensource.org/licenses/mit-license.php).
This product includes software developed by the OpenSSL Project for use in the [OpenSSL Toolkit](https://www.openssl.org/).
cryptographic software written by Eric Young ([eay@cryptsoft.com](mailto:eay@cryptsoft.com)), and UPnP software written by Thomas Bernard.
