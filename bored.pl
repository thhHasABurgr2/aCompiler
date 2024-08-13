
$dir = "/toyCompiler/Lexar/*.c";
@files = glob( $dir );

foreach (@files ) {
   print $_ . "\n";
}
