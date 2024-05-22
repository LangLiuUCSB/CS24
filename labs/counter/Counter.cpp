#include "Counter.h"

// Counter Member Functions
Counter::Counter() {}
Counter::~Counter() {}

size_t Counter::count() const {}
int Counter::total() const {}

void Counter::inc(const std::string &key, int by = 1) {}
void Counter::dec(const std::string &key, int by = 1) {}
void Counter::del(const std::string &key) {}
int Counter::get(const std::string &key) const {}
void Counter::set(const std::string &key, int count) {}

Counter::Iterator Counter::begin() const {}
Counter::Iterator Counter::end() const {}