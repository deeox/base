/*
 *  Copyright (C) 1997-2016 JDE Developers Team
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see http://www.gnu.org/licenses/.
 *  Authors :
 *       Aitor Martinez Fernandez <aitor.martinez.fernandez@gmail.com>
 */
#include <jderobot/comm/rgbdClient.hpp>


namespace Comm {

RgbdClient*
getRgbdClient(Comm::Communicator* jdrc, std::string prefix){
	RgbdClient* client = 0;

	int server;
	std::string server_name = jdrc->getConfig().asString(prefix+".Server");
	server = server2int(server_name);

	switch (server){
		case 0:
		{
			std::cout << "Rgbd disabled" << std::endl;
			break;
		}
		case 1:
		{
			std::cout << "Receiving RgbD from ICE interfaces" << std::endl;
			RgbdIceClient* cl;
			cl = new RgbdIceClient(jdrc, prefix);
			cl->start();
		    client = (Comm::RgbdClient*) cl;
		    break;
		}
		case 2:
		{
			#ifdef JDERROS
				/*std::cout << "Receiving Image from ROS messages" << std::endl;
				std::string nodeName;
				nodeName =  jdrc->getConfig().asStringWithDefault(prefix+".Name", "LaserNode");
				std::string topic;
				topic = jdrc->getConfig().asStringWithDefault(prefix+".Topic", "");
				ListenerRgbd* lc;
				lc = new ListenerRgbd(0, nullptr, nodeName, topic);
				lc->start();
				client = (Comm::RgbdClient*) lc;*/
				throw "ERROR: RGBD is not supported with ROS yet";
            #else
				throw "ERROR: ROS is not available";
			#endif

		 	break;
		}
		default:
		{
			std::cerr << "Wrong " + prefix+".Server property" << std::endl;
			break;
		}

	}

	return client;


}

}//NS
