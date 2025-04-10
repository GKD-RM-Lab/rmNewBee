#include<cstdint>
#pragma pack(push, 1)


//消息类型
enum MessageType{
    ORDER_REQUEST = 1,
    ORDER_RESPONSE = 2
};

struct MessageHeader{
    uint32_t msgLength;
    uint8_t msgType;
};

//订单要求型消息
struct OrderHeader {
    uint32_t customerId;
    uint16_t itemCount;
};

struct OrderItem {
    uint16_t foodId;
    uint16_t quantity;
};
//订单回应型消息
struct OrderResponse{
    uint32_t customerId;
    int8_t result; //整体结果(1成功/-1失败)
    uint32_t itemCount;

    struct {
        uint16_t foodId;
        int8_t itemResult; // 每个菜品的结果(1成功/-1失败)
    } items[]; 
};



#pragma pack(pop)