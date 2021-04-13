OS="$(dpkg-architecture -q DEB_BUILD_ARCH)"
case $OS in
*"amd64"*)
  echo "AMD64"
  base_dir=PosturePerfectionReceiver_1.0.0-1_amd64
  control_file=debPackages/CONTROL_AMD64 
  ;;
*"armhf"*)
  echo "ARMHF"
  base_dir=PosturePerfectionReceiver_1.0.0-1_armhf
  control_file=debPackages/CONTROL_ARMHF 
  ;;
*)
  printf "Not possible to build"
  exit 1
  ;;
esac

cmake build .
sudo make install 

cd Examples/PosturePerfection
cmake build .

cd ../../

mkdir -p $base_dir/usr/local
mkdir $base_dir/DEBIAN
cp $control_file $base_dir/DEBIAN/control
cd $base_dir/usr/local
mkdir bin
mkdir lib
mkdir -p share/PosturePerfection
mkdir include
cd ../../..
cp Examples/PosturePerfection/PosturePerfectionReceiver $base_dir/usr/local/bin
cp libRemoteNotifyReceive.a $base_dir/usr/local/lib
cp RemoteNotifyReceive.h $base_dir/usr/local/include
cp Examples/PosturePerfection/posture-logo-no-text.png $base_dir/usr/local/share/PosturePerfection/

dpkg-deb --build --root-owner-group $base_dir
rm -r $base_dir



