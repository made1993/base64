#include "../include/base64.h"

byte base64code(byte in){
	return b64alf[in];
}
int _encodeb64(byte *in, byte *out){
	byte aux =0;
	if (in == NULL || out == NULL)
			return 1;
	out[0] = b64alf[(in[0] >> 2)];
	
	aux = (in[0] & 0x03) << 4;
	out[1] = b64alf[(aux | (in[1] >> 4))];
	
	aux = (in[1] & 0x0F) << 2;
	out[2] = b64alf[(aux | (in[2] >> 6))];
	
	out[3] = b64alf[ in[2] >> 2];
	
	return 0;
}
int _encodeb64Last(byte *in, byte *out, int len){
	if(len > 2 || len < 1)
		return 1;
	out[0] = b64alf[(in[0] >> 2)];
	
	aux = (in[0] & 0x03) << 4;
	out[1] = b64alf[(aux | (in[1] >> 4))];
	
	aux = (in[1] & 0x0F) << 2;
	out[2] = b64alf[(aux | (in[2] >> 6))];
	
	out[3] = b64alf[ in[2] >> 2];
	
	return 0;


}
int encodeb64v2(byte *in, byte **out, int inlen){
	int size = 0;
	int posIn = 0;
	int posOut = 0;
	if (inlen < 1 || in  == NULL || out == NULL)
		return -1;
	size = (inlen/3) * 4;
	if(inlen %3 > 1)
		size += 4;
	size++;
	*out =  malloc(size);
	while(posIn <= inlen){
		_encodeb64(&(in[posIn]), &(*out)[posOut]);
		posIn += 3;
		posOut += 4;
	}

	out[size -1] =  '\0';
	return size;
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
			value |= in[pos/8 -1] & 0x3F; 

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
