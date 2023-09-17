# Password Manager

***
__About__
Password manager with a user interface on QT. Access to the application is protected by hashing, and all data is stored in an SQL table in encrypted form using the AES-128 algorithm.

***
__How to__
At the first launch, the program will prompt you to set a password by entering it twice. The password is stored in a hashed form in the SQL file 'mydatabase.db,' and the hash ID is always listed as 0 in the table. After registration, you can add a new username and password at the top of the window. Passwords are stored in an encrypted form using the AES-128 algorithm. Currently, changing the login password without data loss is not possible, but you can delete the 'mydatabase.db' file. In that case, all data will be permanently lost, but you can register again.

***
__Used technologies__

C++
Qt
SQlite
OpenSSL
