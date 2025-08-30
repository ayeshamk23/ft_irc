// #include "Server.hpp"
// #include "Client.hpp"
#include "Channel.hpp"
#include <vector>
#include <string>

void handleTopic(Server &server, Client &client, std::vector<std::string> &params) {
    if (params.empty()) {
        client.write(":" + server.getServerName() + " 461 " + client.getNickName() + " TOPIC :Not enough parameters\r\n");
        return;
    }

    std::string channelName = params[0];
    Channel* channel = server.getChannel(channelName);

    // 1. Check if channel exists
    if (!channel) {
        client.write(":" + server.getServerName() + " 403 " + client.getNickName() + " " + channelName + " :No such channel\r\n");
        return;
    }

    // 2. Check if client is in the channel
    if (!channel->hasMember(client.getFd())) {
        client.write(":" + server.getServerName() + " 442 " + client.getNickName() + " " + channelName + " :You're not on that channel\r\n");
        return;
    }

    // 3. If no new topic provided → show current topic
    if (params.size() == 1) {
        if (channel->getTopic().empty())
            client.write(":" + server.getServerName() + " 331 " + client.getNickName() + " " + channelName + " :No topic is set\r\n");
        else
            client.write(":" + server.getServerName() + " 332 " + client.getNickName() + " " + channelName + " :" + channel->getTopic() + "\r\n");
        return;
    }

    // 4. If +t is set, only operators can change the topic
    if (channel->isTopicRestricted() && !channel->isOperator(client.getNickName())) {
        client.write(":" + server.getServerName() + " 482 " + client.getNickName() + " " + channelName + " :You're not channel operator\r\n");
        return;
    }

    // 5. Set new topic
    std::string newTopic = params[1];
    if (newTopic[0] == ':')
        newTopic.erase(0, 1);  // Remove ':' from the beginning

    for (size_t i = 2; i < params.size(); ++i)
        newTopic += " " + params[i];

    channel->setTopic(newTopic);

    // 6. Broadcast topic change
    channel->broadcast(":" + client.getPrefix() + " TOPIC " + channelName + " :" + newTopic + "\r\n");
}