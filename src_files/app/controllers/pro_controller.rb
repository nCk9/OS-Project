class ProController < ApplicationController
    def index
        Jobpool.delete_all
        for counter in 1..15
            time=rand(20)+1
            @post=Jobpool.new(:num=>counter,:wt=>time)
            @post.save
        end
        
        @jobcount=Jobpool.count
        
        
    end
end
