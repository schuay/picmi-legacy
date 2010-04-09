# Maintainer: Jakob Gruber (jakob gruber kabelnet at)

pkgname=picmi
pkgver=1.1.3
pkgdesc="A number logic game."
pkgrel=1
arch=('i686' 'x86_64')
url="http://github.com/schuay/$pkgname/"
license=('GPL')
depends=('sdl_gfx' 'sdl_image' 'sdl_ttf' 'qt')
makedepends=('git' 'boost')

build() {

  # clean source directory
  rm -rf $srcdir/*

  # git checkout
  cd $srcdir || return 1
  git clone git://github.com/schuay/$pkgname.git || return 1
  cd $srcdir/$pkgname || return 1
  git checkout -b installer $pkgname-$pkgver || return 1

  # set file path
  sed -i 's_#define FILEPREFIX.*_#define FILEPREFIX "/usr/share/picmi/"_' src/b_painter.h || return 1

  # build
  qmake || return 1
  make || return 1

  # install
  mkdir -p $pkgdir/usr/{bin,share/{applications,$pkgname/gfx}}
  install -D -m755 $pkgname $pkgdir/usr/bin/
  install -D -m644 src/$pkgname.desktop $pkgdir/usr/share/applications/
  install -D -m644 \
    gfx/* $pkgdir/usr/share/$pkgname/gfx/

  # create symbolic link to old executable path
  cd $pkgdir/usr/bin
  ln -s $pkgname tuxpicross
}
