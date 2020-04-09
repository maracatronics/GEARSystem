echo "updating apt repo"
sudo apt update
sudo apt upgrade

echo "Installing Dependencies"

sudo apt install -y build-essential g++ libqt4-dev libeigen3-dev protobuf-compiler libprotobuf-dev omniorb omniidl omniorb-nameserver libomniorb4-dev