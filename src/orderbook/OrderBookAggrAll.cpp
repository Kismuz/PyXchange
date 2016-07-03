/**
 * @brief   Implementation of orderbook, aggregate price levels for given client
 * @file    OrderBookAggrAll.cpp
 *
 * Copyright (c) 2016 Pavel Schön <pavel@schon.cz>
 *
 */


#include "orderbook/OrderBook.hpp"
#include "client/Client.hpp"
#include "utils/Constants.hpp"
#include "utils/Side.hpp"


namespace pyxchange
{

namespace py = boost::python;


/**
 * @brief Aggregate price levels for given client
 * @param client which has logged in
 *
 */
void OrderBook::aggregateAllPriceLevels( const ClientPtr& client ) const
{
    aggregateAllPriceLevels<BidOrderContainer>( bidOrders, client, side::bid_ );
    aggregateAllPriceLevels<AskOrderContainer>( askOrders, client, side::ask_ );
}


/**
 * @brief Aggregate set of price levels in given orders container, notify clients
 * @param orders OrdersContainer (bid or ask)
 * @param client which has logged in
 * @param side of orders
 *
 */
template<typename OrderContainer>
inline void OrderBook::aggregateAllPriceLevels( const typename OrderContainer::type& orders,
                                                const ClientPtr& client, const side_t side_ ) const
{
    const auto& idxPrice = orders.template get<tags::idxPrice>();

    auto outerIt = idxPrice.begin();

    while( outerIt != idxPrice.end() )
    {
        const price_t priceLevel = (*outerIt)->price;
        quantity_t quantity = 0;

        const auto  innerEnd = idxPrice.upper_bound( priceLevel );
              auto  innerIt  = idxPrice.lower_bound( priceLevel );

        while( innerIt != innerEnd )
        {
            quantity += (*innerIt)->quantity;

            ++outerIt;
            ++innerIt;
        }

        client->notifyOrderBook( priceLevel, side_, quantity );
    }
}


} /* namespace pyxchange */


/* EOF */

