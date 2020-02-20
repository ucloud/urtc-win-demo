# UCloudRTC win SDK API 手册

* [引擎接口 类](#class)
    * [获取引擎](#class-UCloudRtcEngine)
    * [销毁引擎](#class-destroy)
    * [注册时间监听](#class-regRtcEventListener)
    
<a name='class'></a>

## 1. class UcloudRtcEngine引擎接口类

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
