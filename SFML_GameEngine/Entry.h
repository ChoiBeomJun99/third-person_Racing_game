#pragma once

//¿£Æ®¸® Å¬·¡½º
//¿£Æ®¸® Å¬·¡½º´Â ¿ì¼±¼øÀ§ Å¥¿¡ µé¾î°¥ ÀÚ·áÇüÀ» Á¤ÀÇÇÑ´Ù
/* Å° ¯“°ú µ¥ÀÌÅÍ °ªÀ» ÀúÀåÇÑ´Ù
»ý¼ºÇÒ ¶§, µ¥ÀÌÅÍ °ªÀÇ Å¸ÀÔÀ» Á¤ÀÇÇØ ÁÖ¾î¾ß ÇÑ´Ù.
*/
template <typename T>
class Entry {
public : 
	T data;//µ¥ÀÌÅÍ °ª
	int key;//Å° °ª
	Entry(T data, int key) {
		this->data = data;
		this->key = key;
	}
};