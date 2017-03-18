#include "rpc/impl/rpc_factory_impl.h"
#include "rpc/impl/add_node_request.h"
#include "rpc/impl/out_of_date_notification.h"
#include "rpc/impl/remove_node_request.h"
#include "utils/hash.h"
namespace rpc {

std::unique_ptr<RPC>
RPCFactoryImpl::createRPC(const std::string &data,
                          net::Client& client) {
    // parce binary data to RPC

    utils::Hash hash;
    char c = data.at(0);
    switch (c) {
    case 'a': {
        node::NodeInfo ni;
        return std::make_unique<AddNodeRequest>(client,
                                                std::move(ni),
                                                hash);
    }
    case 'r': {
        std::string ip;
        return std::make_unique<RemoveNodeRequest>(client,ip, hash);
    }
    case 'u': {
        return std::make_unique<OutOfDateNotification>(client, hash);
    }
    default:
        break;
    }
}

}  // namespace
