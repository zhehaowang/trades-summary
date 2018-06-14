#ifndef INCLUDED_TRADE
#define INCLUDED_TRADE

#include <chrono>
#include <string>

namespace tradebook {

class Trade {
  public:
    typedef unsigned int Quantity;
    typedef unsigned int Price;
    typedef std::chrono::microseconds Timestamp;
  public:
    Trade(const Timestamp&   timestamp,
          const std::string& symbol,
          Quantity           quantity,
          Price              price);
    Trade(uint64_t           timestamp,
          const std::string& symbol,
          Quantity           quantity,
          Price              price);

    Timestamp   timestamp() const;
    std::string symbol()    const;
    Quantity    quantity()  const;
    Price       price()     const;
  private:
    Timestamp   d_timestamp;
    std::string d_symbol;
    Quantity    d_quantity;
    Price       d_price;
};

inline
Trade::Trade(const Timestamp&   timestamp,
             const std::string& symbol,
             Trade::Quantity    quantity,
             Trade::Price       price)
 : d_timestamp(timestamp),
   d_symbol(symbol),
   d_quantity(quantity),
   d_price(price)
{}

inline
Trade::Trade(uint64_t           timestamp,
             const std::string& symbol,
             Trade::Quantity    quantity,
             Trade::Price       price)
 : d_timestamp(std::chrono::duration<uint64_t>(timestamp)),
   d_symbol(symbol),
   d_quantity(quantity),
   d_price(price)
{}

inline
Trade::Timestamp Trade::timestamp() const {
    return d_timestamp;
}

inline
std::string Trade::symbol() const {
    return d_symbol;
}

inline
Trade::Quantity Trade::quantity() const {
    return d_quantity;
}

inline
Trade::Price Trade::price() const {
    return d_price;
}

}

#endif