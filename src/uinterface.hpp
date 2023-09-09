#pragma once

#include "session.hpp"

class uinterface_t {
    session_t session;
    bool display_metadata(session_t* session);
};

class console_interface_t: public uinterface_t {
};
