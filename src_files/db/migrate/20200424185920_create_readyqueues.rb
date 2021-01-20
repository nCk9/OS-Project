class CreateReadyqueues < ActiveRecord::Migration[6.0]
  def change
    create_table :readyqueues do |t|
      t.integer :num
      t.integer :wt

      t.timestamps
    end
  end
end
