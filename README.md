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

[中文/Chinese](README_zh.md)

> QNet is an open-source project that wraps the QNetworkAccessManager class in C++11, aiming to provide a more concise and user-friendly network access tool. The project references the cpr project and has been improved and optimized based on this foundation.


## build and run

### Installation

You can install QNet by following these commands:

```C++
git clone https://github.com/kevinlq/QNet.git
cd QNet
mkdir build && cd build
cmake ..
make
sudo make install
```

### Using

In your C++ code, include the QNet header file:

```C++
#include "QNet.h"

```

- get request

```
auto response = QNet::Get(QNet::QQUrl{"http://www.example/api"},
                              QNet::QHeader{{QNetworkRequest::ContentTypeHeader, "application/json"}},
                              QNet::QTimeOut{20000});
```

debug result:
```C++
    qDebug() << "url: " << response.m_url;
    qDebug() << "elapsed:" << response.m_elapsed;
    qDebug() << "httpCode: " << response.m_statusCode ;
    qDebug() << "errorCode: " << response.m_replayError;
    qDebug() << "errorString: " << response.m_replayErrorString;
    qDebug() << "data:" << response.m_responseData;
```

- post request
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


## Documentation and Contributions

For more information about QNet and how to use it, please refer to the README.md file. If you have any questions or suggestions, feel free to submit issues or pull requests. We also welcome you to contribute to QNet!

Please read [CONTRIBUTING.md](#) for details on our code of conduct, and the process for submitting pull requests to us.

## Acknowledgments

Thank [cpr](#) for the open-source project.

## Release History

* V 0.0.1


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

