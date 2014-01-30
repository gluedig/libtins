#include "dot11/dot11_action.h"

#ifdef HAVE_DOT11

#include <cstring>
#include <cassert>

namespace Tins {
/* Action */

Dot11Action::Dot11Action(const address_type &dst_hw_addr, 
  const address_type &src_hw_addr,
  ActionCategory category, uint8_t action) 
: Dot11ManagementFrame(dst_hw_addr, src_hw_addr) 
{
    this->subtype(Dot11::ACTION);
    this->_body.category = category;
    this->_body.action = action;
}

Dot11Action::Dot11Action(const uint8_t *buffer, uint32_t total_sz) 
: Dot11ManagementFrame(buffer, total_sz) 
{
    uint32_t sz = management_frame_size();
    buffer += sz;
    total_sz -= sz;
    if(total_sz < sizeof(_body))
        throw malformed_packet();
    memcpy(&_body, buffer, sizeof(_body));
    buffer += sizeof(_body);
    total_sz -= sizeof(_body);
    parse_tagged_parameters(buffer, total_sz);
}

uint32_t Dot11Action::header_size() const {
    return Dot11ManagementFrame::header_size() + sizeof(this->_body);
}

uint32_t Dot11Action::write_fixed_parameters(uint8_t *buffer, uint32_t total_sz) {
    uint32_t sz = sizeof(this->_body);
    #ifdef TINS_DEBUG
    assert(sz <= total_sz);
    #endif
    memcpy(buffer, &this->_body, sz);
    return sz;
}

void Dot11Action::category(ActionCategory new_category) {
    this->_body.category = new_category;
}

void Dot11Action::action(uint8_t new_action) {
    this->_body.action = new_action;
}
} // namespace Tins

#endif // HAVE_DOT11
