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
//		std::cout<<"Default constructor" <<std::endl;
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
//		std::cout<<"Copy Constructor called" <<std::endl;
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
		std::cout<<"Using printMagnitude function." <<std::endl;
		std::cout<<"Printing components: (" <<getx() <<"," <<gety() <<"," <<getz() <<")" <<std::endl;
	}
//destructor
	~field(){
	delete[] value;
//	std::cout<<"Default destructor" <<std::endl;
	}
};

class Electric : public field
{
	private:
	double E;
	public:
	Electric() : field (){
//		std::cout<<"Derived default E called" <<std::endl;
	}
	Electric(double x, double y, double z) : field(x, y ,z){
//		std::cout<<"Derived modify E called" <<std::endl;
		} 
	Electric(Electric &copy) : field(copy){
//		std::cout<<"Derived copy E called" <<std::endl;
	}
//functions
/*This is from the function requested in Assignment 8. We are calculating the Electric field with given Total Electric Charge and distance from center.*/
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
/*For some reason, overloading the = operator feels necessary in order for the function to work properly*/
	void operator=(const Electric &other)
	{
		this->setx(other.getx());
		this->sety(other.gety());
		this->setz(other.getz());
	}
	friend std::ostream& operator<<(std::ostream& out, const Electric& field) 
	{
        	out <<"(" <<field.getx() <<"," <<field.gety() <<"," <<field.getz() <<")" <<std::endl;
        	return out;
	}
//destructor
	~Electric(){
//	std::cout<<"This is being deleted: "<<this->getx() <<this->gety() <<this->getz() <<std::endl;
//	std::cout<<"Derived Destructor E called" <<std::endl;
	}
};

class Magnetic : public field
{
	private:
	double M;
	public:
	Magnetic() : field(){
//	std::cout<<"Derived default M called" <<std::endl;
	}
	Magnetic(double x, double y, double z) : field(x,y,z){
//	std::cout<<"Derived modify M called" <<std::endl;
	}
//field functions(current and distance)
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
	friend std::ostream& operator<<(std::ostream& out, const Magnetic& field)
        {       
                out <<"(" <<field.getx() <<"," <<field.gety() <<"," <<field.getz() <<")" <<std::endl;
                return out;
        }
//destructor
	~Magnetic(){
//	std::cout<<"Derived Destrutor M called" <<std::endl;	
	}
};

int main()
{

Electric field1;					//using the default constructor (0,0,0)
std::cout<<"Printing Field1 vector: " <<field1;		//using the overload << operator

Electric field2(10,20,30);				//using the construct that takes 3 parameters and assigns them to the respective coordinates
std::cout<<"Printing Field 2 vector: " <<std::endl;	
field2.printMagnitude();				//using the printMagnitude function

//setting values to field 1 
field1.setx(30);
field1.sety(40);
field1.setz(100);

std::cout<<"Printing setted Field 1 vector:" <<field1;


Electric field3(field2);				//using the copy constructor to copy values of field2 onto field3
std::cout<<"Printing field 3: " <<field3;

/*Demonstrating the operator overload of the + operator given in the example of Assignment 8*/
Electric field4;		
field4 = field1+field2;
std::cout<<"Printing the values of Field 4: " <<field4;

/*Calculating the Electric field of Field 3 given the two parameters*/
field3.calculateEfield(3.2e-19,26.5e-12);
std::cout<<"The Electric Field from a total Charge of 3.2e-19 at 5e-12 meters away is :" <<std::endl;
std::cout<<field3.getE() <<std::endl;

/*Working with the Magnetic Field class*/
Magnetic M1(4,5,6);					//using the parameter constructor inherited from the base class	
std::cout<<"Printing M1 field: " <<M1;			//Printing field using the << overloaded operator

/*calculating the Magnatic field given the two parameters*/
M1.calculateMfield(100,0.06);				//current and distance parametners
std::cout<<"Print magnitude of Magnetic field from a 100A wire 0.06 meters away:  " <<std::endl;
std::cout<<M1.getM() <<std::endl;

/*Using the copy constructor*/
Magnetic M2(M1);
std::cout<<"Print values of M2 that were copied from M1: " <<M2;

/*using default constructor*/
Magnetic M3;
M3 = M1+M2;						//using the overload + operator
std::cout<<"This the Magnitude of M3 = M1 + M2: " <<M3;


return 0;
}
