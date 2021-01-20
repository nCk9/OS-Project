class SimController < ApplicationController
  helper_method :pre
def pre
  
end
    def simulation
        @jsize=Jobpool.count
        @rsize=Readyqueue.count
        @job=Jobpool.all
        @ready=Readyqueue.all
        if (@jsize>0 || @rsize>0)
          if(@rsize<5 && @jsize>0)
              while( @rsize<5 && @jsize>0)
                  @j=Jobpool.first.delete
                  @sav=Readyqueue.new(:num=>@j[:num],:wt=>@j[:wt])
                  @sav.save
                  @rsize=Readyqueue.count
                  @jsize=Jobpool.count
              end
              else
                for i in 1..@rsize
                  @j=Readyqueue.first.delete
                  a=@j[:wt]
                  a=a-2
                  if a>0
                  @sav=Readyqueue.new(:num=>@j[:num],:wt=>a)
                  @sav.save
                end
              end
          end
        end
    end
    
    
   
end
