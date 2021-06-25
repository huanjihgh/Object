# Object
这是一个c++的Object库，可以动态的创建对象，可以像其他语言一样使用Model操作mysql数据库和json对象  
  
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
      
  
  
  
