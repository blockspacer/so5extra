require 'mxx_ru/binary_unittest'

path = 'test/so_5_extra/shutdowner/many_subscribers_stenv'

MxxRu::setup_target(
	MxxRu::BinaryUnittestTarget.new(
		"#{path}/prj_s.ut.rb",
		"#{path}/prj_s.rb" )
)
