# Maintainer: Jakob Gruber (jakob gruber kabelnet at)

pkgname=picmi
pkgver=1.1.7
pkgdesc="A picross and minesweeper clone."
pkgrel=1
arch=('i686' 'x86_64')
url="http://github.com/schuay/$pkgname/"
license=('GPL')
source=("http://github.com/schuay/$pkgname/tarball/$pkgname-$pkgver")
md5sums=('a6edd987ea407d7d6ee6032c8495c63b')
depends=('sdl_gfx' 'sdl_image' 'sdl_ttf' 'qt')
makedepends=('boost')

build() {

  # github names tag downloads after the tag commit
  cd $srcdir/schuay-$pkgname-$pkgname-$pkgver-0-g9afa53a || return 1

  # build
  qmake || return 1
  make setpath || return 1	#sets gfx path in source files
  make || return 1
  make INSTALL_ROOT=$pkgdir install || return 1
}
