sudo apt install -y libmysqlcppconn-dev
sudo apt install -y mysql-server
sudo systemctl start mysql
g++ aims.cpp -lmysqlcppconn
sudo mysql
create user if not exists 'AIMS_admin'@'localhost' identified by '12Tm34Kc@#$%';
grant all privileges on AIMS.*  to 'AIMS_admin'@'localhost';
