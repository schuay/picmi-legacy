# Maintainer: Jakob Gruber (jakob gruber kabelnet at)
 
_pkgname=picross
pkgname=tuxpicross
pkgver=1.0.0
pkgdesc="A number logic game."
pkgrel=1
arch=('i686' 'x86_64')
url="http://github.com/schuay/$_pkgname/"
license=('GPL')
depends=('sdl' 'sdl_gfx' 'sdl_image' 'sdl_ttf' 'imagemagick' 'qt')
makedepends=('git')

build() {

  #clean source directory
  rm -rf $srcdir/*

  #git checkout
  cd $srcdir || return 1
  git clone git://github.com/schuay/$_pkgname.git || return 1
  cd $srcdir/$_pkgname || return 1
  git checkout -b installer $_pkgname-1.0.0 || return 1

  #set file path
  sed -i 's_#define FILEPREFIX.*_#define FILEPREFIX "/usr/share/tuxpicross/"_' src/f_sdldefines.h || return 1

  # START:  QT ENABLED. if you want to disable qt, remove qt from depends(),
  #         comment this section and uncomment the QT DISABLED section

  qmake || return 1
  make || return 1

  # END: QT ENABLED
  # START: QT DISABLED
  #
  # cd $srcdir/$_pkgname/src || return 1
  # make || return 1
  # mv tuxpicross ../picross
  # cd $srcdir/$_pkgname || return 1
  #
  # END: QT DISABLED

  mkdir -p $pkgdir/usr/{bin,share/{applications,$pkgname/gfx}}
  install -D -m755 $_pkgname $pkgdir/usr/bin/$pkgname
  install -D -m644 src/$pkgname.desktop $pkgdir/usr/share/applications/$pkgname.desktop
  install -D -m644 \
    gfx/* $pkgdir/usr/share/$pkgname/gfx/

}
