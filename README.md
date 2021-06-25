# Object
这是一个c++的Object库，可以动态的创建对象，可以像其他语言一样使用Model操作mysql数据库和json对象  
只需要使用头文件#include "HLib.h",  
HLib.h 文件在include目录里面
1、Object是对象的基类，其他所有类都继承Object，下面是使用的例子：  
  
 （1）、定义一个Result对象  
  /*** 
	**	author:huangguoheng  
	**	email:470136534@qq.com  
	**	date:2021-05-08  
	**	description:  
	**/  
	class Result :public object::Object  
	{  
	public:  
		virtual std::string identify() const {  
			return "Result";//声明一个唯一的标识，可以通过这个动态创建对象，生成json字符串和转换成json对象  
		};		
		//声明字段  
		FIELD(int, opt)//操作  
		FIELD(bool, success)   
		FIELD(std::string, result)   
		FIELD(std::string, msg)   
		FIELD(Array, datas)  
		//映射字段  
		BeginMapField(Result, Object)  
		MapField(Result, int, opt)  
		MapField(Result, bool, success)	  	
		MapField(Result, std::string, result)  
		MapField(Result, std::string, msg)  
		MapField(Result, Array, datas)  
		EndMapField  
	};    
  （2）、下面可以用Json类来生成Json字符串或者把json字符串转成Result对象。  
      	Result rs;  
	//json字符串转换成对象  
	Json json("{\"opt\":1,\"success\":true,\"result\":\"hello world\",\"datas\":[\"1\",\"2\",\"3\"]}");          
        if(json.ToObject(rs)){  
            std::count<<rs.getresult()<<"\n";  
        }  
        //对象转换成json字符串  
        auto jsonStr=json.ToString(rs);  
	  
2、动态的创建一个对象
	//注册自定义的类Result
	object::Type::registerType(u8"Result", [] { return std::make_shared< Result>(); })  
	//初始化默认定义的类和刚刚自定义的类类型
	object::Type::initStaticType();   
	//构造一个默认类型的对象
	auto x= object::Type::construct("Int32");  
	//转换对象到相应的类型  
	auto x2 = object::cast<object::Int32>(x);  
	//下面可以直接使用该对象了
	x2=100;
	//自定义对象Result的使用和上面一样  
	//构造对象  
	auto x= object::Type::construct("Result");  
	//转换对象到相应的类型  
	auto x2 = object::cast<Result>(x);  
	//使用对象
	x2.setsuccess(true)  
	x2.setopt(1 )  
      
  
  
  
