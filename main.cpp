#include <iostream>

#define E_0 8.854e-12
#define PI 3.14159
#define mu 12.566e-7


class field
{
	private:
	double *value;
	public:
//constructor
	field(){
		value = new double[3];
		*value = 0;
		*(value+1)= 0;
		*(value+2) = 0;
		std::cout<<"Default constructor" <<std::endl;
	}
	field(double x, double y, double z){
		value = new double[3];
		*value = x;
		*(value+1) = y;
		*(value+2) = z;		
	}
	field(field &copy)
	{
		value = new double[3];
		*value = copy.value[0];
		*(value+1) = copy.value[1];
		*(value+2) = copy.value[2];
		std::cout<<"Copy Constructor called" <<std::endl;
	}
//setters
	void setx(double x){
		*value = x;
	}
	void sety(double y){
		*(value+1) = y;
	}
	void setz(double z){
		*(value+2) =z;
	}


//getters
	double getx() const{
		return *value;
	}
	double gety() const{
		return *(value+1);
	}
	double getz() const{
		return *(value+2);
	}
//function
	void printMagnitude()
	{
		std::cout<<"Printing components of field: (" <<getx() <<"," <<gety() <<"," <<getz() <<")" <<std::endl;
	}
//operator + overload
//destructor
	~field(){
	delete[] value;
	std::cout<<"Default destructor" <<std::endl;
	}
};

class Electric : public field
{
	private:
	double E;
	public:
	Electric() : field (){
		std::cout<<"Derived default E called" <<std::endl;}
	Electric(double x, double y, double z) : field(x, y ,z){
		std::cout<<"Derived modify E called" <<std::endl;} 
	Electric(Electric &copy) : field(copy){
		std::cout<<"Derived copy E called" <<std::endl;
	}
//functions
	void calculateEfield(double Q, double r)
	{
		E = (Q)/(4*PI*r*r*E_0);
	}
//getter
	double getE()
	{
		return E;
	}	
//overload functions
	Electric operator+(const Electric& other)
	{
		double x = this->getx() + other.getx();
//		std::cout<<"x = " <<x <<std::endl;
		double y = this->gety() + other.gety();
//		std::cout<<"y = " <<y <<std::endl;
		double z = this->getz() + other.getz();
//		std::cout<<"z = " <<z <<std::endl;
		Electric sum;
		sum.setx(x);
//		std::cout<<sum.getx() <<std::endl;
		sum.sety(y);
//		std::cout<<sum.gety() <<std::endl;
		sum.setz(z);
//		std::cout<<sum.getz() <<std::endl;
		return sum;
	}
	void operator=(const Electric &other)
	{
		this->setx(other.getx());
		this->sety(other.gety());
		this->setz(other.getz());
	}
//destructor
	~Electric(){
	std::cout<<"This is being deleted: "<<this->getx() <<this->gety() <<this->getz() <<std::endl;
	std::cout<<"Derived Destructor E called" <<std::endl;
	}
};

class Magnetic : public field
{
	private:
	double M;
	public:
	Magnetic() : field(){
	std::cout<<"Derived default M called" <<std::endl;
	}
	Magnetic(double x, double y, double z) : field(x,y,z){
	std::cout<<"Derived modify M called" <<std::endl;
	}
//field functions
	void calculateMfield(double I, double r)
	{
		M = (I*mu)/(2*PI*r); 
	}
//getter
	double getM()
	{
		return M;
	}
//operator overload functions
	Magnetic operator+(const Magnetic& other)
	{
		double x = this->getx() + other.getx();
		double y = this->gety() + other.gety();
		double z = this->getz() + other.getz();
		Magnetic sum;
		sum.setx(x);
		sum.sety(y);
		sum.setz(z);
		return sum;
	}
	void operator=(const Magnetic& other)
	{
		this->setx(other.getx());
		this->sety(other.gety());
		this->setz(other.getz());
	}
//destructor
	~Magnetic(){
	std::cout<<"Derived Destrutor M called" <<std::endl;	
	}
};

int main()
{

Electric field1;
std::cout<<"Printing Field1 vector: " <<std::endl;
field1.printMagnitude();

Electric field2(10,20,30);
std::cout<<"Prinitng Field 2 vector: ";
field2.printMagnitude();

//setting values
field1.setx(30);
field1.sety(40);
field1.setz(100);

std::cout<<"Printing setted Field 1 vector:" <<std::endl;
field1.printMagnitude();

//Electric field3(field1+field2);
//std::cout<<"Printing copy of field 2 in field 3" <<std::endl;
//field3.printMagnitude();

Electric field4;
//field3 = field1.operator+(field2);
field4 = field1+field2;
//field3.printMagnitude();
field4.printMagnitude();

//field3.calculateEfield(3.2e-19,26.5e-12);
//std::cout<<"The Electric Field from a total Charge of 3.2e-19 at 5e-12 meters away is :" <<std::endl;
//std::cout<<field3.getE() <<std::endl;
//std::cout<<field3 <<std::endl;


Magnetic M1(4,5,6);
std::cout<<"Printing M1 field: " <<std::endl;
M1.printMagnitude();



M1.calculateMfield(100,0.06);
std::cout<<"Print magnitude of Magnetic field from a 100A wire 0.06 meters away:  " <<std::endl;
std::cout<<M1.getM() <<std::endl;

Magnetic M2(10,10,10);
Magnetic M3;

M3 = M1+M2;
std::cout<<"This the Magnitude of M3 = M1 + M2: " <<std::endl;
M3.printMagnitude();


return 0;
}
