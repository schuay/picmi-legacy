# Maintainer: Jakob Gruber (jakob gruber kabelnet at)
 
_pkgname=picross
pkgname=tuxpicross
pkgver=0.1
pkgdesc="A number logic game."
pkgrel=4
arch=('i686' 'x86_64')
url="http://github.com/schuay/$_pkgname/"
license=('GPL')
depends=('sdl' 'sdl_gfx' 'sdl_image' 'sdl_ttf' 'imagemagick')
makedepends=('git')

build() {

  #clean source directory
  rm -rf $srcdir/*

  #git checkout
  cd $srcdir || return 1
  git clone git://github.com/schuay/$_pkgname.git || return 1
  cd $srcdir/$_pkgname/src || return 1

  #build
  make || return 1
  make install DESTDIR=$pkgdir || return 1
}

