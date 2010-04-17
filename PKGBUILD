# Maintainer: Jakob Gruber (jakob gruber kabelnet at)

pkgname=picmi
pkgver=1.1.4
pkgdesc="A picross and minesweeper clone."
pkgrel=1
arch=('i686' 'x86_64')
url="http://github.com/schuay/$pkgname/"
license=('GPL')
source=("http://github.com/schuay/$pkgname/tarball/$pkgname-$pkgver")
md5sums=('cef548e5cb7783bfbe59a403ea4d9461')
depends=('sdl_gfx' 'sdl_image' 'sdl_ttf' 'qt')
makedepends=('boost')

build() {

  # github names tag downloads after the tag commit
  cd $srcdir/schuay-$pkgname-5763396 || return 1

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
