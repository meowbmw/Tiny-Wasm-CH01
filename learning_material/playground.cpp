#include <iostream>
#include <variant>
#include <vector>
#include <string>
#include <stdexcept>
#include <type_traits>
#include <typeinfo>
#include "../vector_print.h"

using namespace std;
class VariantArray {
public:
    // 定义一个可以存储 int, double 和 std::string 的 variant
    using VarType = std::variant<int, double, std::string>;

    // 函数模板，用于将不同类型的变量 push 到数组中
    template <typename T>
    void push(T value) {
        varArray.push_back(value);
    }

    // 函数模板，用于通过索引访问 VarType 中存储的值
    template <typename T>
    T get(size_t index) const {
        if (index >= varArray.size()) {
            throw std::out_of_range("Index out of range");
        }
        return std::get<T>(varArray[index]);
    }

    // 函数模板，用于通过索引访问 VarType 中存储的值并实例化一个对应的变量
    void instantiateVariable(size_t index) const {
        if (index >= varArray.size()) {
            throw std::out_of_range("Index out of range");
        }

        // 使用 std::visit 访问 variant 中的值并实例化一个对应的变量
        std::visit([](auto&& value) {
            using T = std::decay_t<decltype(value)>;
            T variable = value; // 实例化一个对应类型的变量
            std::cout << "Instantiated variable of type " << typeid(T).name() << " with value: " << variable << std::endl;
        }, varArray[index]);
    }

    // 函数用于打印 VarType 中存储的值
    void print() const {
        for (const auto& var : varArray) {
            std::visit([](const auto& value) {
                std::cout << value << std::endl;
            }, var);
        }
    }

private:
    // 定义一个 vector 来存储 VarType
    std::vector<VarType> varArray;
};

int main() {
  vector<int> v={1, 2, 3, 4};
  cout << v;
  // VariantArray va;
  // va.push(42);            // push int
  // va.push(3.14);          // push double
  // va.push("Hello World"); // push std::string

  // std::cout << "Contents of the array:" << std::endl;
  // va.print();

  // std::cout << "Accessing elements by index:" << std::endl;
  // try {
  //     std::cout << "Element at index 0: " << va.get<int>(0) << std::endl;
  //     std::cout << "Element at index 1: " << va.get<double>(1) << std::endl;
  //     std::cout << "Element at index 2: " << va.get<std::string>(2) << std::endl;
  // } catch (const std::bad_variant_access& e) {
  //     std::cerr << "Bad variant access: " << e.what() << std::endl;
  // } catch (const std::out_of_range& e) {
  //     std::cerr << "Index out of range: " << e.what() << std::endl;
  // }

  // std::cout << "Instantiating variables by index:" << std::endl;
  // try {
  //     va.instantiateVariable(0); // 实例化索引 0 处的变量
  //     va.instantiateVariable(1); // 实例化索引 1 处的变量
  //     va.instantiateVariable(2); // 实例化索引 2 处的变量
  // } catch (const std::out_of_range& e) {
  //     std::cerr << "Index out of range: " << e.what() << std::endl;
  // }

  // return 0;
}