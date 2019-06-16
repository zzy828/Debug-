#ifndef _ENUMCLASS
#define _ENUMCLASS
enum typeNum {
	left,
	right,
	mid,
	text
};
struct ArrowMessage {
	unsigned char fire;
	unsigned char weapRank;
	unsigned char weapKind;
	unsigned char picKind;
	char HP;	//ÑªÁ¿
	bool Ai;
	float rotation;
	float x, y;
	//ArrowMessage() {
	//	fire = (unsigned char)(0);
	//}
};
#endif // !_ENUMCLASS

