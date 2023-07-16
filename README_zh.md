<!-- PROJECT SHIELDS -->
<!--
*** I'm using markdown "reference style" links for readability.
*** Reference links are enclosed in brackets [ ] instead of parentheses ( ).
*** See the bottom of this document for the declaration of the reference variables
*** for contributors-url, forks-url, etc. This is an optional, concise syntax you may use.
*** https://www.markdownguide.org/basic-syntax/#reference-style-links
-->
[![Contributors][contributors-shield]][contributors-url]
[![Forks][forks-shield]][forks-url]
[![Stargazers][stars-shield]][stars-url]
[![Issues][issues-shield]][issues-url]
[![MIT License][license-shield]][license-url]
[![LinkedIn][linkedin-shield]][linkedin-url]



<!-- PROJECT LOGO -->
<br />
<p align="center">
  <a href="https://github.com/kevinlq/QNet">
    <img src="images/logo.png" alt="Logo" width="80" height="80">
  </a>

  <h3 align="center">QNet</h3>

  <p align="center">
    QNet
    <br />
    <a href="https://github.com/kevinlq/QNet"><strong>Explore the docs »</strong></a>
    <br />
    <br />
    <a href="https://github.com/kevinlq/QNet">View Demo</a>
    ·
    <a href="https://github.com/kevinlq/QNet/issues">Report Bug</a>
    ·
    <a href="https://github.com/kevinlq/QNet/issues">Request Feature</a>
  </p>
</p>

# QNet

[英语/English](README.md)

> QNet是一个使用 `C++11` 封装了`QNetworkAccessManager`类的开源项目，旨在提供一个更加简洁易用的网络访问工具。该项目参考了cpr项目，并在此基础上进行了改进和优化


## 使用指南

### 安装

你可以通过以下命令安装QNet

```C++
git clone https://github.com/kevinlq/QNet.git
cd QNet
mkdir build && cd build
cmake ..
make
sudo make install
```

### 使用

在你的C++代码中，包含QNet头文件
```C++
#include "QNet.h"

```

- get 请求

```
auto response = QNet::Get(QNet::QQUrl{"http://www.example/api"},
                              QNet::QHeader{{QNetworkRequest::ContentTypeHeader, "application/json"}},
                              QNet::QTimeOut{20000});
```

打印返回结果:
```C++
    qDebug() << "url: " << response.m_url;
    qDebug() << "elapsed:" << response.m_elapsed;
    qDebug() << "httpCode: " << response.m_statusCode ;
    qDebug() << "errorCode: " << response.m_replayError;
    qDebug() << "errorString: " << response.m_replayErrorString;
    qDebug() << "data:" << response.m_responseData;
```

- post 请求
```
    QByteArray ba;
    {
        QJsonObject jsObj;
        jsObj.insert("name", "devstone");
        jsObj.insert("email", "kevinlq0912@gmail.com");

        QJsonDocument jsDoc(jsObj);
        ba = jsDoc.toJson();
    }
    auto response = QNet::Post(QNet::QQUrl{"http://www.example/api"},
                          QNet::QBodyData{QNet::BodyRawJSON, ba},
                          QNet::QTimeOut{20000});
```

    
## 文档与贡献

更多关于QNet的信息和用法，请查看README.md文件。如果你有任何问题或建议，欢迎提交issue或pull request。同时，我们也欢迎你为QNet做出贡献！

查看更多关于这个项目的贡献者，请阅读 [contributors](#)


## 致谢

感谢 [cpr](#) 开源项目


## 版本历史

* V 0.0.1 完成常用的http请求封装


<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->
[contributors-shield]: https://img.shields.io/github/contributors/kevinlq/QNet.svg?style=for-the-badge
[contributors-url]: https://github.com/kevinlq/QNet/graphs/contributors
[forks-shield]: https://img.shields.io/github/forks/kevinlq/QNet.svg?style=for-the-badge
[forks-url]: https://github.com/kevinlq/QNet/network/members
[stars-shield]: https://img.shields.io/github/stars/kevinlq/QNet.svg?style=for-the-badge
[stars-url]: https://github.com/kevinlq/QNet/stargazers
[issues-shield]: https://img.shields.io/github/issues/kevinlq/QNet.svg?style=for-the-badge
[issues-url]: https://github.com/kevinlq/QNet/issues
[license-shield]: https://img.shields.io/github/license/kevinlq/QNet.svg?style=for-the-badge
[license-url]: https://github.com/kevinlq/QNet/blob/master/LICENSE.txt
[linkedin-shield]: https://img.shields.io/badge/-LinkedIn-black.svg?style=for-the-badge&logo=linkedin&colorB=555
[linkedin-url]: https://linkedin.com/in/kevinlq
[cpr-url]: https://github.com/libcpr/cpr

