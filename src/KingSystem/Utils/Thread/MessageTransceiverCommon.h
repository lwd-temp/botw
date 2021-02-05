#pragma once

#include "KingSystem/Utils/Thread/MessageBroker.h"
#include "KingSystem/Utils/Thread/MessageDispatcherBase.h"

namespace ksys {

template <class T>
bool sendMessageImpl(T* transceiver, const MesTransceiverId& dest, const MessageType& type,
                     void* user_data, bool ack) {
    MessageDispatcherBase* dispatcher = transceiver->getDispatcher();
    const bool ok = dispatcher->sendMessage(*transceiver->getReceiver()->getId(), dest, type,
                                            user_data, ack, false);

    if (ok)
        transceiver->getReceiver()->setFlag(ack);

    return ok;
}

template <class T>
bool sendMessageOnProcessingThreadImpl(T* transceiver, const MesTransceiverId& dest,
                                       const MessageType& type, void* user_data, bool ack) {
    MessageDispatcherBase* dispatcher = transceiver->getDispatcher();
    const bool ok = dispatcher->sendMessageOnProcessingThread(*transceiver->getReceiver()->getId(),
                                                              dest, type, user_data, ack, false);

    if (ok)
        transceiver->getReceiver()->setFlag(ack);

    return ok;
}

template <class T>
bool sendMessageImpl(T* transceiver, IMessageBroker& broker, const MessageType& type,
                     void* user_data, bool ack) {
    MessageDispatcherBase* dispatcher = transceiver->getDispatcher();
    const bool ok =
        dispatcher->sendMessage(*transceiver->getReceiver()->getId(),
                                *transceiver->getRegister(broker), type, user_data, ack, false);

    if (ok) {
        for (int i = 0, n = broker.countTransceivers(); i < n; ++i)
            transceiver->getReceiver()->setFlag(ack);
    }

    return ok;
}

template <class T>
bool sendMessageOnProcessingThreadImpl(T* transceiver, IMessageBroker& broker,
                                       const MessageType& type, void* user_data, bool ack) {
    MessageDispatcherBase* dispatcher = transceiver->getDispatcher();
    const bool ok = dispatcher->sendMessageOnProcessingThread(*transceiver->getReceiver()->getId(),
                                                              *transceiver->getRegister(broker),
                                                              type, user_data, ack, false);

    if (ok) {
        for (int i = 0, n = broker.countTransceivers(); i < n; ++i)
            transceiver->getReceiver()->setFlag(ack);
    }

    return ok;
}

}  // namespace ksys