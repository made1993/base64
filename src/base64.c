#include "../include/base64.h"

byte base64code(byte in){
	return b64alf[in];
}
int encodeb64(byte* in, byte** out, int inlen){

	int nbits = 0, pos = 0, arrpos = 0;
	byte value = 0;
	if(inlen < 1 || in  == NULL || out == NULL)
		return 0;
	nbits = inlen * 8;
	*out = NULL;
	if(nbits%6 == 0)
		*out =  malloc(nbits/6);
	else
		*out =  malloc(nbits/6 +2);

	do{
		value = 0;
		pos += 6;
		if(pos % 8 == 6){ 
			/*0xFC*/
			value = in[pos/8];
			value >>=2;
		}
		else if(pos % 8 == 4){
			/*0x03*/
			value = in[pos/8 -1] & 0x03;
			value <<= 4;
			value |= in[pos/8] >>4;

		}
		else if(pos % 8 == 2){
			/*0X0F*/
			value = in[pos/8 -1] & 0x0F;
			value <<= 2;
			value |= in[pos/8] >>6;
		}
		else{
			/*0x3F*/
			value |= in[pos/8 -1] & 0x2F; 

		}
		(*out)[arrpos++] = base64code(value);
	}while(nbits- pos > 5);
	if(nbits- pos < 6){
		value = 0;
		value |= in[pos/8] << (8 - (nbits- pos));
		value >>= 2;
		printf("%d\n", (int)value);
		(*out)[arrpos++] = base64code(value);		
		(*out)[arrpos++] = '=';
	}
	return arrpos;
}

int main(void)
{
   char* out = NULL;
   printf("%d %d %d\n\n", 'M', 'a', 'n');
   encodeb64("M", (unsigned char**) &out, 1);
   printf("%s\n", out);
   free(out);
   return 0;
}