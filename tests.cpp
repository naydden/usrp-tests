//
// Copyright 2014 Ettus Research LLC
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//

// This tiny program is meant as an example on how to set up UHD
// projects using CMake.
// The program itself only initializes a USRP. For more elaborate examples,
// have a look at the files in host/examples/.

#include <uhd/utils/thread_priority.hpp>
#include <uhd/utils/safe_main.hpp>
#include <uhd/usrp/multi_usrp.hpp>
#include <boost/program_options.hpp>
#include <boost/format.hpp>
#include <iostream>
#include <chrono>
#include <thread>

namespace po = boost::program_options;

int UHD_SAFE_MAIN(int argc, char *argv[]){
    uhd::set_thread_priority_safe();

    //variables to be set by po
    std::string args;

    //setup the program options
    po::options_description desc("Allowed options");
    desc.add_options()
        ("help", "help message")
        ("args", po::value<std::string>(&args)->default_value(""), "multi uhd device address args")
    ;
    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    //print the help message
    if (vm.count("help")){
        std::cout << boost::format("Mini-example to initialize a USRP (args==%s).") % args << std::endl;
        return ~0;
    }

    //create a usrp device
    std::cout << std::endl;
    std::cout << boost::format("Creating the usrp device with: %s...") % args << std::endl;
    uhd::usrp::multi_usrp::sptr usrp = uhd::usrp::multi_usrp::make(args);
    std::string gpio_bank = "FP0";

    // // set up our masks, defining the pin numbers
    // #define MAN_GPIO_MASK   (1 << 6)
    // #define ATR_MASKS       MAN_GPIO_MASK
    // #define ATR_CONTROL     MAN_GPIO_MASK
    // #define GPIO_DDR        MAN_GPIO_MASK

    // // assume an existing USRP device handle, called "usrp_x300"
    // // now, let's do the basic ATR setup
    // std::cout << ATR_CONTROL << std::endl;
    // std::cout << ATR_MASKS << std::endl;
    // std::cout << GPIO_DDR << std::endl;
    // std::cout << std::endl;
    // usrp->set_gpio_attr("FP0", "CTRL", ATR_CONTROL, ATR_MASKS);
    // usrp->set_gpio_attr("FP0", "DDR", GPIO_DDR, ATR_MASKS);
    // // // let's manually set GPIO4 high
    // usrp->set_gpio_attr("FP0", "OUT", 1, MAN_GPIO_MASK);
    
    // std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    // std::cout << usrp->get_gpio_attr("FP0", "OUT") << std::endl;
    // std::cout << "bye bye" << std::endl;


//              J504
//            ---------
// fp_gpio<0> | 1 | 2 | fp_gpio<1>
//            ---------
// fp_gpio<2> | 3 | 4 | fp_gpio<3>
//            ---------
// fp_gpio<4> | 5 | 6 | fp_gpio<5>
//            ---------
// fp_gpio<6> | 7 | 8 | fp_gpio<7>
//            ---------
//        gnd | 9 | 10| gnd
//            ---------

    // When mentioning pin X I refer to the physical one.
    /******* TEST 1*************/
    // Set all pins manual mode 
    // usrp->set_gpio_attr(gpio_bank, "CTRL", 0x00, 0xff);

    // // Set all four pins to be output pins
    // usrp->set_gpio_attr(gpio_bank, "DDR", 0xff, 0xff);

    // // Manually set all GPIO pins high
    // usrp->set_gpio_attr(gpio_bank, "OUT", 0xff, 0xff);

    /******* TEST 2*************/
    // // Set all pins in manual mode 
    // usrp->set_gpio_attr(gpio_bank, "CTRL", 0x00, 0xff);

    // // Set all pins to be output pins
    // usrp->set_gpio_attr(gpio_bank, "DDR", 0xff, 0xff);

    // // Manually set 2 GPIO pin high
    // usrp->set_gpio_attr(gpio_bank, "OUT", 0xff, 0x2);

    /******* TEST 3*************/
    // // Set all pins in manual mode 
    // usrp->set_gpio_attr(gpio_bank, "CTRL", 0x00, 0xff);

    // // Set all pins to be output pins
    // usrp->set_gpio_attr(gpio_bank, "DDR", 0xff, 0xff);

    // // Manually set GPIO pins 1 and 2 to high
    // // 0x30 in hex = 0011 0000 in binary
    // usrp->set_gpio_attr(gpio_bank, "OUT", 0xff, 0x3);

    /******* TEST 4*************/
    // Set all pins in manual mode 
    usrp->set_gpio_attr(gpio_bank, "CTRL", 0x00, 0xff);

    // Set all pins to be output pins
    usrp->set_gpio_attr(gpio_bank, "DDR", 0xff, 0xff);

    // Manually set GPIO pins 1 and 2 to low
    // 0x30 in hex = 0011 0000 in binary
    usrp->set_gpio_attr(gpio_bank, "OUT", 0x00 , 0x3);    


    return EXIT_SUCCESS;
}
