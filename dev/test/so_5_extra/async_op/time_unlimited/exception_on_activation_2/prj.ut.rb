require 'mxx_ru/binary_unittest'

path = 'test/so_5_extra/async_op/time_unlimited/exception_on_activation_2'

MxxRu::setup_target(
	MxxRu::BinaryUnittestTarget.new(
		"#{path}/prj.ut.rb",
		"#{path}/prj.rb" )
)
