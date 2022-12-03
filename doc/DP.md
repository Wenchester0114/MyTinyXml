# Design Proposal of XML framework
## 1 整体设计思路
### 1.1 梗概
先读取整个文件，把文件流转换为字符流，然后把整个xml文档当作一个大字符串来处理。
例如：
```xml
<?xml version="1.0" encoding="UTF-8"?>
<!--This is commnets-->
<!--This is commnets-->


<bookstore>
    <book category="COOKING">
        <!--This is commnets-->
        <title lang="en">Everyday Italian</title>
        <author>Giada De Laurentiis</author>
        <year>2005</year>
        <!--This is commnets-->
        <price>30.00</price>
    </book>
    <book category="CHILDREN">
        <title lang="en">Harry Potter</title>
        <author>J K. Rowling</author>
        <year>2005</year>
        <price>29.99</price>
    </book>
    <book category="WEB">
        <title lang="en">Learning XML</title>
        <author>Erik T. Ray</author>
        <year>2003</year>
        <price>39.95</price>
    </book>
</bookstore>



```
我们可以分为以下几种情况：
* 解析文件头
  1. 这部分不重要，直接忽略
  2. 遇到`<?`开始，遇到`?>`结束
* 解析注释
  1. 这部分不重要，直接忽略
  2. `<!--`开始，`-->`结束
* 解析节点
  1. 解析节点名
     1. `<`且紧随其后的是字母，从该字母开始算节点名，当遇到非字母时停止
  2. 解析属性
     1. 解析完节点名字后， 如果后面跟着的不是`>`则开始解析属性，遇到`=`key解析完毕；遇到`"`开始解析value，再次遇到解析完毕
  3. 解析文字
     1. 很简单`>`开始`<`结束
  4. 解析子节点
     1. 遇到</..>开始差
     2. 递归实现
### 1.2 需要提前了解的知识
* c++基础语法，面向对象思想
* STL: string, list, map
* xml
* 算法: 递归
* 数据结构: 链表，树
## 2 XML基础
https://www.runoob.com/xml/xml-validator.html



