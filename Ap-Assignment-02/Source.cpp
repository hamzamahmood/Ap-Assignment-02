/****************************
*	HamzaMahmood 33093 CS4B *
*****************************/
#include <iostream>
using namespace std;

/*===========================================String Buffer Implementation========================================*/
class StringBuffer {
public:
	StringBuffer();						//default constructor
	~StringBuffer();					//destructor; would delete the allocated buffer
	StringBuffer(const StringBuffer&);	//copy constructor deep copy
	StringBuffer(char*, int);			//constructor to convert a char* to StringBuffer

	char charAt(int) const;				//returns the character at the passed index
	int length() const;                 //returns the length of the buffer
	void reserve(int);                  //allocates memory for the string, according to the passed character length
	void append(char);                  //appends a single character at the end
	char* copy() const;					//return deep copy of the _strbuf
	char* shallow() const;				//return address of _strbuf
private:
	char* _strbuf;                      //buffer to store the original string
	int _length;                        //length of the string
};
//default copy constructor
StringBuffer::StringBuffer() {
	this->_length = 0;
	this->_strbuf = NULL;
}
//Destructor of StringBuffer
StringBuffer::~StringBuffer() {
	_length = 0;
	if (this->_strbuf != NULL) {
		delete this->_strbuf;
		this->_strbuf = NULL;
	}
}
//copy a const StringBuffer into this string
StringBuffer::StringBuffer(const StringBuffer& newString) {
	this->_length = newString._length;
	this->_strbuf = new char[_length];
	for (int i = 0; i < _length; i++) {
		_strbuf[i] = newString._strbuf[i];
	}
}
//converting a char[] to StringBuffer (Two arg. constructor)
StringBuffer::StringBuffer(char* a, int b) {
	this->_length = b;
	this->_strbuf = new char[b];
	for (int i = 0; i < b; i++) {
		this->_strbuf[i] = a[i];
	}
}
//returns a character at location l
char StringBuffer::charAt(int l) const {
	if (l < this->_length) {
		return this->_strbuf[l];
	}
	else {
		return 0;
	}
}
//returns the length of StringBuffer
int StringBuffer::length() const {
	return this->_length;
}
//reserver memory of length n
void StringBuffer::reserve(int n) {
	this->_strbuf = new char[n];
	this->_length = n;
}
//append char to the StringBuffer
void StringBuffer::append(char a) {
	if (this->_strbuf == NULL) {
		return;
	}
	char* temp = new char[_length + 1];
	this->_length = _length + 1;
	int i;
	for (i = 0; i < this->_length; i++) {
		if (_strbuf[i] == '\0') {
			break;
		}
		temp[i] = this->_strbuf[i];
	}
	temp[i] = a;
	temp[i + 1] = '\0';
	delete this->_strbuf;
	this->_strbuf = temp;
	temp = NULL;
}
//returns new copy of the _strbuf
char* StringBuffer::copy()const {
	char* temp = new char[this->_length];
	for (int i = 0; i < _length; i++) {
		temp[i] = this->_strbuf[i];
	}
	return temp;
}
char* StringBuffer::shallow()const {
	return this->_strbuf;
}
/*=========================================COPY STRING POINTER=========================================*/
class CopyStringPtr {
public:
	CopyStringPtr();					//default constructor
	CopyStringPtr(const CopyStringPtr&);//copy constructor deep copy
	CopyStringPtr(char*, int);			//copy constructor deep copy
	~CopyStringPtr();					//destructor for memory cleanup

	char* getStringBuffer() const;		//returns the StringBuffer 
	char charAt(int) const;				//returns the character at the passed index
	int length() const;                 //returns the length of the buffer
	void reserve(int);                  //allocates memory for the string, according to the passed character length
	void append(char);                  //appends a single character at the end
private:
	StringBuffer* ptr;
};
CopyStringPtr::CopyStringPtr() {
	ptr = new StringBuffer();
}
CopyStringPtr::CopyStringPtr(const CopyStringPtr& nptr) {
	ptr = new StringBuffer(nptr.getStringBuffer(), nptr.length());
}
CopyStringPtr::CopyStringPtr(char* a,int b) {
	ptr = new StringBuffer(a, b);
}
CopyStringPtr::~CopyStringPtr() {
	ptr->~StringBuffer();
	delete ptr;
	ptr = NULL;
}
char* CopyStringPtr::getStringBuffer() const {
	return ptr->copy();
}
char CopyStringPtr::charAt(int l) const{
	return ptr->charAt(l);
}
int CopyStringPtr::length() const {
	return ptr->length();
}
void CopyStringPtr::reserve(int n) {
	ptr->reserve(n);
}
void CopyStringPtr::append(char a) {
	ptr->append(a);
}
/*==========================================OWNED POINTERS=========================================*/
class OwnedStringPtr {
public:
	OwnedStringPtr();					//default constructor
	OwnedStringPtr(OwnedStringPtr&);	//copy constructor shallow copy with owner ship transfer
	OwnedStringPtr(char*, int);			//copy constructor deep copy
	~OwnedStringPtr();					//destructor for memory cleanup

	char* getStringBuffer() const;		//returns the StringBuffer
	char* getShallowBuffer() const;		//return shallow copy of _strbuf
	char charAt(int) const;				//returns the character at the passed index
	int length() const;                 //returns the length of the buffer
	void reserve(int);                  //allocates memory for the string, according to the passed character length
	void append(char);                  //appends a single character at the end

private:
	StringBuffer* ptr;
	bool owner;
};
OwnedStringPtr::OwnedStringPtr() {
	ptr = new StringBuffer();
	owner = true;
}
OwnedStringPtr::OwnedStringPtr(OwnedStringPtr& nptr) {
	ptr = new StringBuffer(nptr.getShallowBuffer(), nptr.length());
	nptr.owner = false;
	this->owner = true;
}
OwnedStringPtr::OwnedStringPtr(char* a, int b) {
	ptr = new StringBuffer(a, b);
	this->owner = true;
}
OwnedStringPtr::~OwnedStringPtr() {
	if (this->owner == true) {
		ptr->~StringBuffer();
		delete ptr;
		ptr = NULL;
	}
	else {
		ptr = NULL;
	}
}
char* OwnedStringPtr::getShallowBuffer() const{
	return ptr->shallow();
}
char* OwnedStringPtr::getStringBuffer() const {
	return ptr->copy();
}
char OwnedStringPtr::charAt(int l) const{
	return ptr->charAt(l);
}
int OwnedStringPtr::length() const {
	return ptr->length();
}
void OwnedStringPtr::reserve(int n) {
	ptr->reserve(n);
}
void OwnedStringPtr::append(char a) {
	ptr->append(a);
}
/*================================================MAIN=================================================*/
int main() {
	char* a = "Hello World";
	char* b = "classic war worlds timothy hines entertaining film obviously"
	"goes great effort lengths faithfully recreate h g wells classic book "
	"mr hines succeeds watched film appreciated fact standard predictable hollywood fare comes every year e g "
	"spielberg version tom cruise slightest resemblance book obviously everyone looks different things movie envision amateur "
	"critics look criticize everything others rate movie important bases like entertained people never agree critics enjoyed effort mr hines "
	"put faithful h g wells classic novel found entertaining made easy overlook critics perceive shortcomings";
	printf("%s\n", b);
	CopyStringPtr b1 = CopyStringPtr(a,sizeof(a)+ 1);
	CopyStringPtr b2 = CopyStringPtr(b, sizeof(b) + 1);

	return 0;
}