class CreateJobpools < ActiveRecord::Migration[6.0]
  def change
    create_table :jobpools do |t|
      t.integer :num
      t.integer :wt

      t.timestamps
    end
  end
end
