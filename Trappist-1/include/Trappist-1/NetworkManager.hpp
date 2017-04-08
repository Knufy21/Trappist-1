#pragma once

#include <SFML\Network.hpp>
#include <Trappist-1\util\Timer.hpp>



class NetworkManager
{
	enum class PacketIdentifier : sf::Uint8
	{
		PING,
		PONG,

	};

public:
	static constexpr unsigned short TRAPPIST_1_SERVER_PORT = 32768 + 15;

	NetworkManager()
	{
		this->localIpAddress = sf::IpAddress::getPublicAddress();
	}

	~NetworkManager()
	{
		disconnect();
	}

	void connect(const sf::IpAddress &ipAddress)
	{
		// Connect Tcp-Socket
		tcpSocket.connect(ipAddress, NetworkManager::TRAPPIST_1_SERVER_PORT);
		this->remoteIpAddress = tcpSocket.getRemoteAddress();

		// Bind Udp-Socket
		udpSocket.bind(sf::Socket::AnyPort);
		localPort = udpSocket.getLocalPort();
	}

	void disconnect()
	{
		// Disconnect Tcp-Socket
		tcpSocket.disconnect();

		// Unbind Udp-Socket
		udpSocket.unbind();
	}

	void updatePing()
	{
		sf::IpAddress pongAddress;
		unsigned short pongPort;

		// Ping packet
		sf::Packet packet;
		packet << static_cast<sf::Uint8>(PacketIdentifier::PING);

		Timer pinger;
		udpSocket.send(packet, remoteIpAddress, NetworkManager::TRAPPIST_1_SERVER_PORT);

		packet.clear();

		// Pong packet
		udpSocket.receive(packet, pongAddress, pongPort);

		ping = static_cast<unsigned short>(pinger.elapsedMilliseconds());

		// Check if pong packet and its sender is correct
		sf::Uint8 pongSignal;
		packet >> pongSignal;
		if (pongSignal == static_cast<sf::Uint8>(PacketIdentifier::PING))
		{
			if (pongPort == NetworkManager::TRAPPIST_1_SERVER_PORT && pongAddress == remoteIpAddress)
			{

			}
			else
			{
				// Handle wrong sender error
				ping = 0xFFFF;
			}
		}
		else
		{
			// Handle wrong package error
			ping = 0xFFFF;
		}
	}



private:
	sf::IpAddress localIpAddress;	// Client's ip address
	unsigned short localPort;		// Client's port
	sf::IpAddress remoteIpAddress;	// Servers' ip address

	unsigned short ping;			// Client's last ping, retrieved with updatePing()

	sf::TcpSocket tcpSocket;
	sf::UdpSocket udpSocket;
};