#include "hurricane/message/CommandClient.h"
#include "hurricane/message/Command.h"
#include "hurricane/util/NetConnector.h"
#include "hurricane/base/ByteArray.h"
#include <iostream>

namespace hurricane {
	namespace message {
		CommandClient::~CommandClient() {
			if ( _connector ) {
				delete _connector;
				_connector = nullptr;
			}
		}

		void CommandClient::SendCommand(const Command& command, SendCommandCallback callback) {
			try {
				hurricane::base::ByteArray commandBytes = command.Serialize();
				std::cout << commandBytes.size() << std::endl;

				_connector->SendAndReceive(commandBytes.data(), commandBytes.size(), [callback](char* resultBuffer, int32_t readSize) {
					hurricane::message::Response response;
					hurricane::base::ByteArray commandBytes(resultBuffer, readSize);
					response.Deserialize(commandBytes);

					callback(response);
				});
			}
			catch (const char* message) {
				std::cerr << message << std::endl;
				exit(-1);
			}
		}
	}
}