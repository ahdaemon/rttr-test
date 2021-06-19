/**
 * 组件描述：一个非常强大的运行时类型反射库，具备 类型注册，类型反射，获取属性方法列表等。。。
官网: https://www.rttr.org/
git: https://github.com/rttrorg/rttr
version：release 0.9.6

编译步骤
1.wget https://github.com/rttrorg/rttr/archive/refs/tags/v0.9.6.tar.gz
2.tar zxvf v0.9.6.tar.gz && cd rttr-0.9.6
3.修改CMakelist.txt中编译选项，关闭多余的编译过程

    - BUILD_RTTR_DYNAMIC
    - BUILD_UNIT_TESTS
    - BUILD_EXAMPLES
4.cmake -DCMAKE_BUILD_TYPE=Release .

    - 如果cmake版本较低，请进行升级 https://blog.csdn.net/u013714645/article/details/77002555
5.make && make install，执行完后，所需的头文件，lib库都在install目录里
 *
*/

#include <iostream>
#include <string>
#include <vector>

#include "rttr/include/registration.h"
#include "rttr/include/rttr_enable.h"
#include "rttr/include/type.h"

using namespace std;
using namespace rttr;

// -----------------------------------------------------------------
class Step1 {
 public:
  Step1() { cout << "step1 construct called" << endl; };
  virtual ~Step1() {}

  void set_data(uint32_t data) { data_ = data; }
  uint32_t get_data() { return data_; }

 public:
  void func() { cout << "step1 func called, data " << data_ << endl; }
  void func1(uint32_t arg) { cout << "step1 func1 called, arg " << arg << endl; }
  virtual void func2() { cout << "step1 func2 called\n"; }

 private:
  uint32_t data_ = 0;

  RTTR_ENABLE();
};

// -----------------------------------------------------------------
class Step2 {
 public:
  Step2() { cout << "step2 construct called" << endl; }

  void set_data(uint32_t data) { data_ = data; }
  uint32_t get_data() { return data_; }

 public:
  void func() { cout << "step2 func called, data " << data_ << endl; }
  void func1(uint32_t arg) { cout << "step1 func2 called, arg " << arg << endl; }

 private:
  uint32_t data_ = 0;
};

RTTR_REGISTRATION {
  registration::class_<Step1>("Step1")
      .constructor<>()
      .property("data", &Step1::get_data, &Step1::set_data)
      .method("func", &Step1::func)
      .method("func1", &Step1::func1);

  registration::class_<Step2>("Step2")
      .constructor<>()
      .property("data", &Step2::get_data, &Step2::set_data)
      .method("func", &Step2::func)
      .method("func1", &Step2::func1);
};

static const vector<string> steps = {"Step1", "Step2"};

int main(int argc, char** argv) {
  for (auto& step : steps) {
    auto t = type::get_by_name(step);
    auto obj = t.create();

    t.get_method("func").invoke(obj);
    t.get_property("data").set_value(obj, (uint32_t)2);
    t.get_method("func").invoke(obj);

    t.get_method("func1").invoke(obj, (uint32_t)1);
  }

  return 0;
}