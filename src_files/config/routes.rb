Rails.application.routes.draw do





  root 'pro#index'

  get 'simulation' => 'sim#simulation'




  # For details on the DSL available within this file, see https://guides.rubyonrails.org/routing.html
end
