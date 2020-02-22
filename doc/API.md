# UCloudRTC win SDK API 手册

* [UcloudRtcEngine引擎接口 类](#class)
    * [UCloudRtcEngine类 - 获取引擎](#class-UCloudRtcEngine)
    * [destroy类 - 销毁引擎](#class-destroy)
    * [regRtcEventListener类 - 注册时间监听](#class-regRtcEventListener)
    
<a name='class'></a>

## 一. class UcloudRtcEngine引擎接口类

<a name='class-UCloudRtcEngine'></a>

### 1.1  获取引擎

static UCloudRtcEngine *sharedInstance()

**返回值**

UCloudRtcEngine* 引擎类指针

**参数说明**    

无

**消息回调**

无

<a name='class-destroy'></a>

### 1.2  销毁引擎

static void destroy()

**返回值**

无

**参数说明**    

无

**消息回调**

无

<a name='class-regRtcEventListener'></a>

### 1.3  注册时间监听

void regRtcEventListener(UCloudRtcEventListener* listener)

**返回值** 

无

**参数说明**    

| 名称    | 说明 | 数据类型 | 可空 |
| -| -| -| -|
|  listener[in]   | UCloudRtcEventListener eUCloudRtcSdkMode     | Class | N |

**消息回调**

无

<a name='class-getSdkVersion'></a>

### 1.4  获取SDK 版本

static const char *getSdkVersion()

**返回值**

SDK的版本号

**参数说明**    

无

**消息回调**

无

<a name='class-setSdkMode'></a>

### 1.5  设置SDK模式

virtual int setSdkMode (eUCloudRtcSdkMode mode)

**返回值**

参见错误描述。

**参数说明**    

| 名称    | 说明 | 数据类型 | 可空 |
| -| -| -| -|
|  mode[in]   | 1，测试模式 <br> 0，正式模式 <br> 详见eUCloudRtcSdkMode     | enum | N |

**消息回调**

无


<a name='class-setStreamRole'></a>

###  1.6  设置流操作权限

virtual int setStreamRole(eUCloudRtcUserStreamRole role)

**返回值**

参见错误码描述。

**参数说明**    

| 名称    | 说明 | 数据类型 | 可空 |
| -| -| -| -|
|  role[in]   | STREAM_ROLE_PUB，上行 <br> STREAM_ROLE_SUB，下行 <br> STREAM_ROLE_BOTH，双向 <br> 详见UCloudStreamRole说明     | enum | N |

**消息回调**

无


<a name='class-'></a>

###  1.7  设置日志等级

virtual void setLogLevel(eUCloudRtcLogLevel level)

**返回值**

无

**参数说明**    

| 名称    | 说明 | 数据类型 | 可空 |
| -| -| -| -|
|  level[in]   | 日志等级 详见eUCloudRtcLogLevel说明     | enum | N |

**消息回调**

无

