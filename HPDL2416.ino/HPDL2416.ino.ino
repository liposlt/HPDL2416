//By liposlt
//HP HPDL2416测试程序

#define HC595_DS  2
#define HC595_RCK 3
#define HC595_SCK 4
#define A0        5
#define A1        6
#define WR        7
#define CU        8
#define CUE       9
#define CLR       10
#define CE2       11
#define CE1       12
#define BL        13

#define HC595_DS_RESET    digitalWrite(HC595_DS, LOW)
#define HC595_DS_SET      digitalWrite(HC595_DS, HIGH)

#define HC595_ST_CP_RESET digitalWrite(HC595_RCK, LOW)    //RCK
#define HC595_ST_CP_SET   digitalWrite(HC595_RCK, HIGH)

#define HC595_SH_CP_RESET digitalWrite(HC595_SCK, LOW)    //SCK
#define HC595_SH_CP_SET   digitalWrite(HC595_SCK, HIGH)

void setup() {
  // put your setup code here, to run once:
  pinMode(HC595_DS,  OUTPUT);
  pinMode(HC595_RCK, OUTPUT);
  pinMode(HC595_SCK, OUTPUT);
  pinMode(A0,  OUTPUT);
  pinMode(A1,  OUTPUT);
  pinMode(WR,  OUTPUT);
  pinMode(CU,  OUTPUT);
  pinMode(CUE, OUTPUT);
  pinMode(CLR, OUTPUT);
  pinMode(CE2, OUTPUT);
  pinMode(CE1, OUTPUT);
  pinMode(BL,  OUTPUT);

  HPDL_2416_displayfull(3, 1);
  HPDL_2416_displayfull(2, 1);
  HPDL_2416_displayfull(1, 1);
  HPDL_2416_displayfull(0, 1);
  delay(3000);
  HPDL_2416_WriteChar(3, 'A');
  HPDL_2416_WriteChar(2, 'B');
  HPDL_2416_WriteChar(1, 'C');
  HPDL_2416_WriteChar(0, 'D');
  delay(1000);
  HPDL_2416_WriteString("    1234567890987654321    ");
  delay(1000);
}
int i = 0;

void loop() {
  // put your main code here, to run repeatedly:
  if (i > 0x3f)
    i = 0;
  HPDL_2416_WriteChar(3, 0x20 + i);
  HPDL_2416_WriteChar(2, 0x21 + i);
  HPDL_2416_WriteChar(1, 0x22 + i);
  HPDL_2416_WriteChar(0, 0x23 + i);
  delay(500);
  i++;
}

void HPDL_2416_displayfull(int pos, int chr)
{
  digitalWrite(BL,   HIGH);           //非空白显示
  digitalWrite(CLR,  HIGH);
  digitalWrite(CE1,  LOW);            //使能
  digitalWrite(CE2,  LOW);            //使能
  digitalWrite(CUE,  HIGH);
  digitalWrite(CU,   LOW);
  digitalWrite(WR,   LOW);            //使能写
  digitalWrite(A1, (pos & 2) >> 1);
  digitalWrite(A0, (pos & 1));

  HC595SendData(chr);
}

void HPDL_2416_WriteString(char *chr)
{
  int i = 0, temp = 0;
  char *s;
  s = chr;

  while (chr[i] != '\0')
  {
    HPDL_2416_WriteChar(3, chr[i]);
    HPDL_2416_WriteChar(2, chr[i + 1]);
    HPDL_2416_WriteChar(1, chr[i + 2]);
    HPDL_2416_WriteChar(0, chr[i + 3]);
    i++;
    delay(500);
    if (i == (strlen(s) - 3))
      i += 3;
  }
}

void HPDL_2416_WriteChar(int pos, int chr)
{
  digitalWrite(BL,   HIGH);          //非空白显示
  digitalWrite(CLR,  HIGH);
  digitalWrite(CE1,  LOW);           //使能
  digitalWrite(CE2,  LOW);           //使能
  digitalWrite(CUE,  LOW);
  digitalWrite(CU,   HIGH);
  digitalWrite(WR,   LOW);           //使能写
  digitalWrite(A1, (pos & 2) >> 1);
  digitalWrite(A0, (pos & 1));

  HC595SendData(chr);
}

void HC595SendData(int data)
{
  int i = 0;
  for (i = 0; i < 8; i++)
  {
    if (data & 0x80)
      HC595_DS_SET;
    else
      HC595_DS_RESET;
    data <<= 1;
    HC595_SH_CP_SET;  HC595_SH_CP_RESET;
  }
  HC595_ST_CP_SET;
  HC595_ST_CP_RESET;
}
