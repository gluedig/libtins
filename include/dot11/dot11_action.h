
#include "../config.h"

#if !defined(TINS_DOT11_DOT11_ACTION_H) && defined(HAVE_DOT11)

#define TINS_DOT11_DOT11_ACTION_H

#include "../dot11/dot11_mgmt.h"

namespace Tins {
enum ActionCategory {
        SPECTRUM_MANAGEMENT,
        QOS,
        DLS,
        BLOCK_ACK,
        PUBLIC,
        RADIO_MEASUREMENT,
        FAST_BSS_TRANSITION,
        HT,
        SA_QUERY,
        PROTECTED_DUAL_OR_PUBLIC_ACTION,
        WNM,
        TDLS,
        MESH,
        MULTIHOP,
        SELF_PROTECTED,
        RESERVED,
        ERROR = 128
};

/**
 * \brief Class representing an Action frame in the IEEE 802.11 Protocol.
 *
 */
class Dot11Action : public Dot11ManagementFrame {
public:
    /**
     * \brief This PDU's flag.
     */
    static const PDU::PDUType pdu_flag = PDU::DOT11_ACTION;

    /**
     * \brief Constructor for creating a 802.11 Action frame.
     *
     * Constructs a 802.11 Action frame taking the 
     * destination and source hardware address.
     *
     * \param dst_hw_addr The destination hardware address.
     * \param src_hw_addr The source hardware address.
     */
    Dot11Action(const address_type &dst_hw_addr = address_type(), 
                const address_type &src_hw_addr = address_type(),
                ActionCategory category = ActionCategory::ERROR, uint8_t action = 0);

    /**
     * \brief Constructs a Dot11Action object from a buffer 
     * and adds all identifiable PDUs found in the buffer as children 
     * of this one.
     * 
     * If the next PDU is not recognized, then a RawPDU is used.
     * 
     * If there is not enough size for the header in the buffer
     * or the input data is malformed, a malformed_packet exception 
     * is thrown.
     *
     * \param buffer The buffer from which this PDU will be constructed.
     * \param total_sz The total size of the buffer.
     */
    Dot11Action(const uint8_t *buffer, uint32_t total_sz);

    /**
     * \brief Getter for the PDU's type.
     * \sa PDU::pdu_type
     */
    PDUType pdu_type() const { return PDU::DOT11_ACTION; }

    /**
     * \brief Check wether this PDU matches the specified flag.
     * \param flag The flag to match
     * \sa PDU::matches_flag
     */
    bool matches_flag(PDUType flag) const {
       return flag == pdu_flag || Dot11ManagementFrame::matches_flag(flag);
    }

    /**
     * \brief Clones this PDU.
     *
     * \sa PDU::clone()
     */
    Dot11Action* clone() const {
        return new Dot11Action(*this);
    }

    /**
     * \brief Returns the frame's header length.
     *
     * \return An uint32_t with the header's size.
     * \sa PDU::header_size()
     */
    uint32_t header_size() const;

    /**
     * \brief Getter for the category field.
     *
     * \return The stored category value.
     */
     ActionCategory category() const { return static_cast<ActionCategory>(_body.category); }

    /**
     * \brief Getter for the action field.
     *
     * \return The stored action value.
     */
    uint8_t action() const { return _body.action; }

    /**
     * \brief Setter for the category field.
     *
     * \param new_category The category to be set.
     */
    void category(ActionCategory new_category);

    /**
     * \brief Setter for the action field.
     *
     * \param new_action The action to be set.
     */
    void action(uint8_t new_action);

private:
    TINS_BEGIN_PACK
    struct Action {
        uint8_t category;
        uint8_t action;
    } TINS_END_PACK;

    Action _body;

    uint32_t write_fixed_parameters(uint8_t *buffer, uint32_t total_sz);

};
} // namespace Tins
#endif // TINS_DOT11_DOT11_ACTION_H
