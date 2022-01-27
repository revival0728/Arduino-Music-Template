const int out_pin = 11;
const int note_length = 300;
const char note_base[7][4] = {"_Do", "_Re", "_Mi", "_Fa", "_So", "_La", "_Si"};
const int freq[21] = {262, 294, 330, 349, 392, 440, 494, 524, 558, 660, 698, 784, 880, 988, 1046, 1175, 1318, 1397, 1568, 1760, 1976};
int hash_table[40];

bool str_comp(const char* a, const char* b) {
  return a[1] == b[1] && a[2] == b[2];
}

int hash(const char* note) {
  int ret = 0;
  if(note[0] == 'm') ret += 10;
  if(note[0] == 'h') ret += 20;
  for(int i = 0; i < 7; ++i) {
    if(str_comp(note_base[i], note))
      ret += i;
  }
  return ret;
}

void setup() {
  // put your setup code here, to run once:
  pinMode(out_pin, OUTPUT);
  Serial.begin(9600);

  char lvl[4] = "lmh";
  for(int i = 0; i < 3; ++i) {
    for(int j = 0; j < 7; ++j) {
      char s[4];
      strcpy(s, note_base[j]);
      s[0] = lvl[i];
      hash_table[hash(s)] = freq[i*7+j];
    }
  }
}

void note(const char* n, int len) {
  tone(out_pin, hash_table[hash(n)], note_length*4.0/len);
  delay(note_length);
}

void rest(int len) {
  delay(note_length*4.0/len);
}

void song() {
  note("mMi", 3);
  note("mMi", 1);
  note("mMi", 3);
  note("mRe", 1);
  note("mDo", 4);
  note("mMi", 4);
  note("mLa", 4);
  note("mSo", 4);
  rest(6);
}

void test() {
  char lvl[4] = "lmh";
  for(int i = 0; i < 3; ++i) {
    for(int j = 0; j < 7; ++j) {
      char s[4];
      strcpy(s, note_base[j]);
      s[0] = lvl[i];
      note(s, 4);
    }
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  test();
  song();
  Serial.print(analogRead(A0));
  Serial.println();
  delay(20);
  if(analogRead(A0) > 0) {
    song();
  }
}