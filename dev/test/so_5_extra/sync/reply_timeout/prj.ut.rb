require 'mxx_ru/binary_unittest'

path = 'test/so_5_extra/sync/reply_timeout'

MxxRu::setup_target(
	MxxRu::BinaryUnittestTarget.new(
		"#{path}/prj.ut.rb",
		"#{path}/prj.rb" )
)
