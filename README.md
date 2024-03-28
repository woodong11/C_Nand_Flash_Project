# C_Nand_Flash_Project
C를 이용해 SSD의 read, write를 구현하고 shell을 자체 제작해 테스트하는 프로젝트입니다. (SSAFY 수업 프로젝트)


## Project Goal
![image](https://github.com/woodong11/C_SSD_project/assets/91379630/5f32b038-75bb-46ca-8532-ef2a5cb6e21c)
<br>SSD에서 controller가 하는 역할을 가상의 C프로그래밍으로 구현하고, NAND Flash는 nand.txt로 대체합니다. <br>
SSD에서 읽어온 값은 result.txt에 저장합니다. <br>
Test Shell에서 SSD 동작을 테스트합니다. <br>
LBA는 4byte, SSD총 용량은 400byte로 가정합니다. <br>
데이터는 32bit unsigned 16진수로 저장됩니다. <br>
<br>
<br>

## How to build
environment: Ubuntu20.04 (GCC compiler, bash shell)

<b> make workspace </b>
```
mkdir ~/ws
```
```
cd ~/ws
```
```
git clone https://github.com/woodong11/C_Nand_Flash_Project.git
```
<br>

<b> build</b>
```
cd ~/ws/C_Nand_Flash_Project
```
```
make -j4
```
<br>

## How to run

<b> run project </b>
```
./test_shell
```
then, SSD_shell will run. 

<b> commands </b><br>
`write` write to SSD       &nbsp; &nbsp; &nbsp;     e.g. `write 3 0xAAAABBBB` <br><br>
`read` read specific LBA  &nbsp; &nbsp; &nbsp;     e.g. `read 3` <br><br>
`fullwrite` write whole SSD  &nbsp; &nbsp; &nbsp;     e.g. `fullwrite 0xAAAABBBB` <br><br>
`fullread` read whole SSD   &nbsp; &nbsp; &nbsp;     e.g. `fullread` <br><br>
`exit` shell terminate  &nbsp; &nbsp; &nbsp;      e.g. `exit` <br><br>
`help` show commands  &nbsp; &nbsp; &nbsp;      e.g. `help` <br><br>




















