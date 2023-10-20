local testing = {}

function testing.eq(lhs, rhs)
  if lhs ~= rhs then
    print(string.format("'%s' != '%s'", lhs, rhs))
    assert(false)
  end
end

return testing
