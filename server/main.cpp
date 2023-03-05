/*
** EPITECH PROJECT, 2023
** main.cpp
** File description:
** main.cpp
*/

#include "Server.hpp"
#include <argparse/argparse.hpp>

int startServer(const Args &args)
{
    rtype::server::GameServer server(args.host, args.tcpPort, args.udpPort, args.maxPlayers);

    try {
        server.init();
    } catch (const std::exception &e) {
        spdlog::error("Error when trying to init the game server: {}", e.what());
        return 1;
    }

    try {
        server.start();
    } catch (const std::exception &e) {
        spdlog::error("Error when trying to start the game server: {}", e.what());
        return 1;
    }

    try {
        server.stop();
    } catch (const std::exception &e) {
        spdlog::error("Error when trying to stop the game server: {}", e.what());
        return 1;
    }

    return 0;
}

int main(int ac, char **av)
{
    auto logger = spdlog::stdout_color_mt("R-Type Server");
    argparse::ArgumentParser program("R-Type Server");
    program.add_description("The R-Type Server");

    program.add_argument("-H", "--host").help("The host to bind the server to").default_value(std::string("0.0.0.0")).metavar("IP");
    program.add_argument("-t", "--tcp-port")
        .help("The TCP port to bind the server to. Must be in [0-65535]")
        .default_value(2409)
        .metavar("PORT")
        .scan<'d', int>();
    program.add_argument("-u", "--udp-port")
        .help("The UDP port to bind the server to. Must be in [0-65535]")
        .default_value(2409)
        .metavar("PORT")
        .scan<'d', int>();
    program.add_argument("-m", "--max-players")
        .help("The maximum number of players allowed on the server")
        .default_value(4)
        .metavar("MAX_PLAYERS")
        .scan<'d', int>();

    try {
        program.parse_args(ac, av);
    } catch (const std::runtime_error &e) {
        logger->error("Error when parsing arguments: {}", e.what());
        return 0;
    } catch (...) {
        logger->error("Unexpected error when parsing arguments");
        return 1;
    }

    std::string host = program.get<std::string>("--host");
    int tcpPort = program.get<int>("--tcp-port");
    int udpPort = program.get<int>("--udp-port");
    int maxPlayers = program.get<int>("--max-players");

    if (host.empty()) {
        logger->error("Invalid host ip: {}", host);
        return 1;
    }

    if (tcpPort < 0 || tcpPort > 65535) {
        logger->error("Invalid TCP port: {}, must be in [0-65535]", tcpPort);
        return 1;
    }

    if (udpPort < 0 || udpPort > 65535) {
        logger->error("Invalid UDP port: {},  must be in [0-65535]", udpPort);
        return 1;
    }

    if (maxPlayers < 0) {
        logger->error("Invalid max players: {}, must be greater than 0", maxPlayers);
        maxPlayers = 4;
        logger->warn("Max players set to 4");
    }

    return startServer({host, static_cast<std::uint16_t>(tcpPort), static_cast<std::uint16_t>(udpPort), maxPlayers});
}
